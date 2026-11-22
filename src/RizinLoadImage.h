// SPDX-FileCopyrightText: 2019-2021 Florian Märkl <info@florianmaerkl.de>
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef RZ_GHIDRA_RizinLOADIMAGE_H
#define RZ_GHIDRA_RizinLOADIMAGE_H

#include "loadimage.hh"

#include <rz_core.h>

// Windows defines LoadImage to LoadImageA
#ifdef LoadImage
#undef LoadImage
#endif

class RzCoreMutex;

class RizinLoadImage : public ghidra::LoadImage
{
	private:
		RzCoreMutex *const core_mutex;
		ghidra::AddrSpaceManager *addr_space_manager;

	public:
		explicit RizinLoadImage(RzCoreMutex *core_mutex, ghidra::AddrSpaceManager *addr_space_manager);

		void loadFill(ghidra::uint1 *ptr, ghidra::int4 size, const ghidra::Address &addr) override;
		void getReadonly(ghidra::RangeList &list) const override;
		std::string getArchType() const override;
		void adjustVma(long adjust) override;

		// True if the flag of an import is on a slot that the loader fills, not on code.
		static bool isImportSlot(RzIO *io, const RzFlagItem *flag);
		// The flag of the import if the address is such a slot, for example in the IAT of a PE.
		static RzFlagItem *importSlotFlag(RzCore *core, ut64 addr);
};

#endif //RZ_GHIDRA_RizinLOADIMAGE_H
