// SPDX-FileCopyrightText: 2024 Crabtux <crabtux@mail.ustc.edu.cn>
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "RizinLoadImage.h"
#include "RizinUtils.h"
#include "PcodeFixupPreprocessor.h"

#include <funcdata.hh>
#include <flow.hh>
#include <override.hh>

using namespace ghidra;

void PcodeFixupPreprocessor::fixupSharedReturnJumpToRelocs(RzAnalysisFunction *function, Funcdata *func, RzCore *core, RizinArchitecture &arch)
{
	RzList *xrefs = rz_analysis_function_get_xrefs_from(function);
	rz_list_foreach_cpp<RzAnalysisXRef>(xrefs, [&](RzAnalysisXRef *xref){
		// To ensure the instruction is a `jmp` instruction
		if (xref->type == RZ_ANALYSIS_XREF_TYPE_CODE)
		{
			// If the target location is a imported function, then do the patch.
			RzBinReloc *reloc = rz_core_get_reloc_to(core, xref->to);
			if (reloc != nullptr && reloc->import != nullptr)
				func->getOverride().insertFlowOverride(Address(arch.getDefaultCodeSpace(), xref->from), Override::CALL_RETURN);
		}
	});
}

void PcodeFixupPreprocessor::fixupCallsThroughImportSlots(RzAnalysisFunction *function, Funcdata *func, RzCore *core, RizinArchitecture &arch)
{
	AddrSpace *importSpace = arch.getImportSpace();
	RzList *xrefs = rz_analysis_function_get_xrefs_from(function);
	if(!importSpace || !xrefs)
	{
		rz_list_free(xrefs);
		return;
	}
	rz_list_foreach_cpp<RzAnalysisXRef>(xrefs, [&](RzAnalysisXRef *xref){
		// A call instruction that refers to an import slot, for example in the IAT of a PE,
		// calls the import behind the slot. As a direct call from the start it gets the
		// prototype of the import in the same way as a call of an import thunk.
		if (xref->type == RZ_ANALYSIS_XREF_TYPE_CALL && RizinLoadImage::importSlotFlag(core, xref->to))
			func->getOverride().insertIndirectOverride(Address(arch.getDefaultCodeSpace(), xref->from), Address(importSpace, xref->to));
	});
	rz_list_free(xrefs);
}

bool PcodeFixupPreprocessor::fixupCallsOfImportSlotValues(Funcdata *func, RzCore *core, RizinArchitecture &arch)
{
	AddrSpace *importSpace = arch.getImportSpace();
	AddrSpace *dataSpace = arch.getDefaultDataSpace();
	if(!importSpace)
		return false;
	bool found = false;
	for(int4 i = 0; i < func->numCalls(); i++)
	{
		PcodeOp *op = func->getCallSpecs(i)->getOp();
		if(op->code() != CPUI_CALLIND)
			continue;
		// The target is the value of an import slot if a copy of the slot comes to the call,
		// for example "call edi" after "mov edi, [IAT slot]".
		Varnode *vn = op->getIn(0);
		bool isSlotValue = false;
		for(;;)
		{
			isSlotValue = vn->getSpace() == dataSpace && vn->getSize() == (int4)dataSpace->getAddrSize() && RizinLoadImage::importSlotFlag(core, vn->getOffset());
			if(isSlotValue || !vn->isWritten() || (vn->getDef()->code() != CPUI_COPY && vn->getDef()->code() != CPUI_CAST))
				break;
			vn = vn->getDef()->getIn(0);
		}
		if(!isSlotValue)
			continue;
		func->getOverride().insertIndirectOverride(op->getAddr(), Address(importSpace, vn->getOffset()));
		found = true;
	}
	return found;
}
