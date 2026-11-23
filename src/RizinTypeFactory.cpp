// SPDX-FileCopyrightText: 2019-2021 Florian Märkl <info@florianmaerkl.de>
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "RizinTypeFactory.h"
#include "RizinArchitecture.h"

#include <rz_core.h>
#include <rz_type.h>

#include <algorithm>
#include <limits>
#include <utility>

#include "RizinUtils.h"

using namespace ghidra;

namespace
{
struct DatatypeFlags : public Datatype
{
	using Datatype::has_bitfields;
};

bool isBitFieldMetatype(type_metatype metatype)
{
	return metatype == TYPE_INT || metatype == TYPE_UINT || metatype == TYPE_BOOL || metatype == TYPE_ENUM_INT || metatype == TYPE_ENUM_UINT
		|| metatype == TYPE_VOID || metatype == TYPE_UNKNOWN;
}
}

RizinTypeFactory::RizinTypeFactory(RizinArchitecture *arch)
	: TypeFactory(arch),
	arch(arch)
{
}

RizinTypeFactory::~RizinTypeFactory()
{
}

Datatype *RizinTypeFactory::addRizinStruct(RzBaseType *type, StackTypes &stack_types, bool prototype)
{
	assert(type->kind == RZ_BASE_TYPE_KIND_STRUCT);

	std::vector<TypeField> fields;
	try
	{
		RzCoreLock core(arch->getCore());
		ut64 offset = 0;
		TypeStruct *r = getTypeStruct(type->name);
		if (prototype) {
			prototypes.insert(r);
			return r;
		} else {
			prototypes.erase(r);
		}
		void *it;
		RzTypeDB *typedb = rz_analysis_get_type_db(core->analysis);
		ut64 layout_size = type->size / 8;
		bool has_layout = layout_size != 0 && layout_size <= (ut64)std::numeric_limits<int4>::max();
		ut64 layout_end = 0;
		std::vector<TypeField> layout_fields;
		bool is_big_endian = arch->getDefaultDataSpace()->isBigEndian();
		bool has_bit_positions = type->struct_data.members.elem_size == sizeof(RzTypeStructMember);
		std::vector<std::pair<ut64, TypeBitField>> bit_members;
		int4 member_index = -1;
		rz_vector_foreach_cpp<RzTypeStructMember>(&type->struct_data.members, [&](RzTypeStructMember *member) {
			member_index++;
			if(!member->type || !member->name)
				return;
			Datatype *member_type = fromRzType(member->type, nullptr, &stack_types);
			if(!member_type)
			{
				char *tstr = rz_type_as_string(typedb, member->type);
				arch->addWarning(std::string("Failed to match type ") + (tstr ? tstr : "?") + " of member " + member->name
						+ " in struct " + type->name);
				rz_mem_free(tstr);
				return;
			}

			// TODO: fix this super obsolete array stuff in struct sdb
			// if(elements > 0)
			// 	memberType = getTypeArray(elements, memberType);

			TypeField tf = {
				(int4)offset, // id = offset by default
				(int4)offset, // Currently, this is 0 most of the time: member->offset,
				std::string(member->name),
				member_type
			};
			fields.push_back(tf);

			ut64 member_size = (ut64)member_type->getSize();
			if(member->size == 0 && (member->offset < layout_end || member->offset > layout_size || member_size > layout_size - member->offset))
				has_layout = false;
			else if(member->size == 0)
			{
				layout_end = member->offset + member_size;
				layout_fields.push_back({(int4)member->offset, (int4)member->offset, std::string(member->name), member_type});
			}
			else if(has_bit_positions && member->bit_end >= member->size && member->bit_end <= layout_size * 8
				&& member->size <= member_size * 8 && isBitFieldMetatype(member_type->getMetatype()))
			{
				ut64 first_bit = member->bit_end - member->size;
				int4 least_bit = (int4)(is_big_endian ? (8 - member->bit_end % 8) % 8 : first_bit % 8);
				Datatype *bit_type = member_type->getMetatype() == TYPE_VOID ? getBase((int4)member_size, TYPE_UNKNOWN) : member_type;
				TypeBitField bit_field(member_index, (int4)member->size, is_big_endian, std::string(member->name), bit_type);
				bit_field.bits.byteOffset = (int4)(first_bit / 8);
				bit_field.bits.leastSigBit = least_bit;
				bit_field.bits.byteSize = (least_bit + (int4)member->size + 7) / 8;
				bit_members.emplace_back(first_bit, bit_field);
			}

			// TODO: right now, we track member offset ourselves
			// which means all structs are assumed to be packed.
			// This should be changed if there is a clear notion of the offset in rizin at some point.
			ut64 packed_size = rz_type_db_get_bitsize(typedb, member->type) / 8;
			offset += packed_size > member_size ? packed_size : member_size;
		});
		std::vector<TypeBitField> bitfields;
		if(has_layout)
		{
			std::stable_sort(bit_members.begin(), bit_members.end(), [](const std::pair<ut64, TypeBitField> &left, const std::pair<ut64, TypeBitField> &right) {
				return left.first < right.first;
			});
			size_t plain_count = layout_fields.size();
			ut64 used_bits_end = 0;
			for(const std::pair<ut64, TypeBitField> &bit_member : bit_members)
			{
				const BitRange &bits = bit_member.second.bits;
				bool overlaps = bit_member.first < used_bits_end;
				for(size_t i = 0; i < plain_count && !overlaps; i++)
				{
					const TypeField &plain = layout_fields[i];
					overlaps = plain.offset < bits.byteOffset + bits.byteSize && bits.byteOffset < plain.offset + plain.type->getSize();
				}
				if(overlaps)
					continue;
				used_bits_end = bit_member.first + (ut64)bits.numBits;
				if(!bits.isByteRange())
				{
					bitfields.push_back(bit_member.second);
					continue;
				}
				Datatype *whole_type = bit_member.second.type;
				if(whole_type->getSize() != bits.byteSize)
				{
					type_metatype metatype = whole_type->getMetatype();
					whole_type = getBase(bits.byteSize, metatype == TYPE_INT || metatype == TYPE_UINT ? metatype : TYPE_UNKNOWN);
				}
				layout_fields.push_back({bits.byteOffset, bits.byteOffset, bit_member.second.name, whole_type});
			}
			if(layout_fields.size() != plain_count)
			{
				std::stable_sort(layout_fields.begin(), layout_fields.end(), [](const TypeField &left, const TypeField &right) {
					return left.offset < right.offset;
				});
			}
		}
		const std::vector<TypeField> &given_fields = has_layout ? layout_fields : fields;
		uint4 flags = bitfields.empty() ? 0 : DatatypeFlags::has_bitfields;
		for(const TypeField &given_field : given_fields)
		{
			if(given_field.type->hasBitfields())
				flags |= DatatypeFlags::has_bitfields;
		}
		int4 align = 1; // TODO: take this from rizin if available in the future
		int4 size = has_layout ? (int4)layout_size : (int4)(offset + rz_num_align_delta(offset, align));
		setFields(given_fields, bitfields, r, size, align, flags);
		return r;
	}

	catch(std::invalid_argument &e)
	{
		arch->addWarning(std::string("Failed to load struct ") + type->name);
		return nullptr;
	}
}

Datatype *RizinTypeFactory::addRizinEnum(RzBaseType *type)
{
	assert(type->kind == RZ_BASE_TYPE_KIND_ENUM);
	std::map<uintb, std::string> namemap;
	rz_vector_foreach_cpp<RzTypeEnumCase>(&type->enum_data.cases, [&](RzTypeEnumCase *ceys) {
		if(!ceys->name)
			return;
		namemap[ceys->val] = ceys->name;
	});
	if(namemap.empty())
		return nullptr;
	try
	{
		auto enumType = getTypeEnum(type->name);
		setEnumValues(namemap, enumType);
		return enumType;
	}
	catch(LowlevelError &e)
	{
		arch->addWarning(std::string("Failed to load enum ") + type->name + ", " + e.explain);
		return nullptr;
	}
}

Datatype *RizinTypeFactory::addRizinTypedef(RzBaseType *type, StackTypes &stack_types)
{
	assert(type->kind == RZ_BASE_TYPE_KIND_TYPEDEF);
	if(!type->type)
		return nullptr;
	Datatype *resolved = fromRzTypeInternal(type->type, nullptr, &stack_types, true, false); // use prototype=true to avoid recursion
	if(!resolved)
		return nullptr;
	Datatype *typedefd = getTypedef(resolved, type->name, 0, 0);
	fromRzTypeInternal(type->type, nullptr, &stack_types, false, false); // fully create the type after querying with prototype=true before
	return typedefd;
}

static type_metatype metatypeOfTypeclass(RzTypeTypeclass tc)
{
	switch(tc)
	{
		case RZ_TYPE_TYPECLASS_NUM:
		case RZ_TYPE_TYPECLASS_INTEGRAL:
		case RZ_TYPE_TYPECLASS_INTEGRAL_UNSIGNED:
			return TYPE_UINT;
		case RZ_TYPE_TYPECLASS_INTEGRAL_SIGNED:
			return TYPE_INT;
		case RZ_TYPE_TYPECLASS_FLOATING:
			return TYPE_FLOAT;
		case RZ_TYPE_TYPECLASS_NONE:
			return TYPE_VOID;
		default:
			return TYPE_UNKNOWN;
	}
}

Datatype *RizinTypeFactory::addRizinAtomicType(RzBaseType *type, StackTypes &stack_types)
{
	assert(type->kind == RZ_BASE_TYPE_KIND_ATOMIC);
	if(!type->name || type->size < 8)
	{
		arch->addWarning(std::string("Invalid atomic type ") + (type->name ? type->name : "(null)"));
		return nullptr;
	}
	RzCoreLock core(arch->getCore());
	RzTypeDB *typedb = rz_analysis_get_type_db(core->analysis);
	type_metatype mt = metatypeOfTypeclass(rz_base_type_typeclass(typedb, type));
	// setCoreType(type->name, type->size / 8, mt, false); // TODO: conditionally enable chartp when supported in rizin
	return getBase(type->size / 8, mt, type->name);
}

Datatype *RizinTypeFactory::queryRizin(const string &n, StackTypes &stack_types, bool prototype)
{
	if(stack_types.find(n) != stack_types.end())
	{
		arch->addWarning("Recursion detected while creating type " + n);
		return nullptr;
	}
	stack_types.insert(n);
	Datatype *r = nullptr;

	RzCoreLock core(arch->getCore());
	RzTypeDB *typedb = rz_analysis_get_type_db(core->analysis);
	RzBaseType *type = rz_type_db_get_base_type(typedb, n.c_str());
	if(!type || !type->name)
		goto beach;
	switch(type->kind)
	{
		case RZ_BASE_TYPE_KIND_STRUCT:
			r = addRizinStruct(type, stack_types, prototype);
			break;
		case RZ_BASE_TYPE_KIND_ENUM:
			r = addRizinEnum(type);
			break;
		case RZ_BASE_TYPE_KIND_TYPEDEF:
			r = addRizinTypedef(type, stack_types);
			break;
		case RZ_BASE_TYPE_KIND_ATOMIC:
			r = addRizinAtomicType(type, stack_types);
			break;
		default:
			break;
	}
beach:
	stack_types.erase(n);
	return r;
}

Datatype *RizinTypeFactory::findById(const string &n, uint8 id, int4 sz, StackTypes &stack_types, bool prototype)
{
	Datatype *r = TypeFactory::findById(n, id, sz);
	if(r && (prototype || prototypes.find(r) == prototypes.end()))
		return r;
	return queryRizin(n, stack_types, prototype);
}

Datatype *RizinTypeFactory::findById(const string &n, uint8 id, int4 sz)
{
	StackTypes stack_types; // to detect recursion
	return findById(n, id, sz, stack_types, false);
}

// prototype means that the type does not have to be completed entirely yet (e.g. struct prototype for typedef)
// refd means that this type is in a pointer of some kind, so we can actually use prototype
// that's because our typedef-likes in ghidra are just clones of the original type, so we must not clone prototypes, only refs.
Datatype *RizinTypeFactory::fromRzTypeInternal(const RzType *ctype, string *error, StackTypes *stack_types, bool prototype, bool refd)
{
	switch(ctype->kind)
	{
		case RZ_TYPE_KIND_IDENTIFIER:
		{
			if(ctype->identifier.kind == RZ_TYPE_IDENTIFIER_KIND_UNION)
			{
				if(error)
					*error = "Union types not supported in Decompiler";
				return nullptr;
			}

			Datatype *r = stack_types ? findByName(ctype->identifier.name, *stack_types, prototype && refd) : findByName(ctype->identifier.name);
			if(!r)
			{
				if(error)
					*error = "Unknown type identifier " + std::string(ctype->identifier.name);
				return nullptr;
			}
			if(ctype->identifier.kind == RZ_TYPE_IDENTIFIER_KIND_STRUCT && r->getMetatype() != TYPE_STRUCT)
			{
				if(error)
					*error = "Type identifier " + std::string(ctype->identifier.name) + " is not the name of a struct";
				return nullptr;
			}
			if(ctype->identifier.kind == RZ_TYPE_IDENTIFIER_KIND_ENUM && !r->isEnumType())
			{
				if(error)
					*error = "Type identifier " + std::string(ctype->identifier.name) + " is not the name of an enum";
				return nullptr;
			}
			return r;
		}
		case RZ_TYPE_KIND_POINTER:
		{
			Datatype *sub = fromRzTypeInternal(ctype->pointer.type, error, stack_types, prototype, true);
			if(!sub)
				return nullptr;
			auto space = arch->getDefaultCodeSpace();
			return this->getTypePointer(space->getAddrSize(), sub, space->getWordSize());
		}
		case RZ_TYPE_KIND_ARRAY:
		{
			Datatype *sub = fromRzTypeInternal(ctype->array.type, error, stack_types, prototype, refd);
			if(!sub)
				return nullptr;
			return this->getTypeArray(ctype->array.count, sub);
		}
		case RZ_TYPE_KIND_CALLABLE:
		{
			RzCallable *callable = ctype->callable;
			ProtoModel *pm = callable->cc ? arch->protoModelFromRizinCC(callable->cc) : nullptr;
			if(!pm)
			{
				RzCoreLock core(arch->getCore());
				const char *cc = rz_analysis_cc_default(core->analysis);
				if(cc)
					pm = arch->protoModelFromRizinCC(cc);
			}
			if(!pm)
			{
				RzCoreLock core(arch->getCore());
				char *tstr = rz_type_as_string(rz_analysis_get_type_db(core->analysis), ctype);
				if (error) {
					*error = std::string("Failed to get any calling convention for callable ") + tstr;
				}
				rz_mem_free(tstr);
				return nullptr;
			}
			Datatype *outtype = nullptr;
			if(callable->ret)
			{
				outtype = fromRzTypeInternal(callable->ret, error, stack_types, prototype, refd);
				if(!outtype)
					return nullptr;
			}
			std::vector<Datatype *> intypes;
			if(!rz_pvector_foreach_cpp<RzCallableArg>(callable->args, [&](RzCallableArg *arg) {
				if(!arg->type)
					return false;
				Datatype *at = fromRzTypeInternal(arg->type, error, stack_types, prototype, refd);
				if(!at)
					return false;
				intypes.push_back(at);
				return true;
			}))
			{
				return nullptr;
			}
			PrototypePieces pcs = { 0 };
			pcs.model = pm;
			if(callable->name)
				pcs.name = callable->name;
			pcs.outtype = outtype;
			pcs.intypes = intypes;
			pcs.firstVarArgSlot = -1; // can be used when rizin supports vararg callables
			return this->getTypeCode(pcs);
		}
	}
	return nullptr;
}

Datatype *RizinTypeFactory::fromRzType(const RzType *ctype, string *error, StackTypes *stack_types)
{
	return fromRzTypeInternal(ctype, error, stack_types, false, false);
}
