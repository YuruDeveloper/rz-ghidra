
all:

.PHONY: clean
clean:
	rm -fv dectest32 dectest64 rec sharedReturn.o

dectest32: dectest.c types.h
	gcc -m32 -fno-pic -no-pie -fno-omit-frame-pointer -o dectest32 -O0 dectest.c

dectest32-sp: dectest.c types.h
	gcc -m32 -fno-pic -no-pie -fomit-frame-pointer -o dectest32-sp -O0 dectest.c

dectest64: dectest.c types.h
	gcc -m64 -fno-pic -no-pie -fno-omit-frame-pointer -o dectest64 -O0 dectest.c

dectest64-sp: dectest.c types.h
	gcc -m64 -fno-pic -no-pie -fomit-frame-pointer -o dectest64-sp -O0 dectest.c

rec: rec.c types_rec.h
	gcc -m64 -fno-pic -no-pie -fno-omit-frame-pointer -o rec -O0 rec.c

strings: strings.c
	gcc -m64 -fno-pic -no-pie -fno-omit-frame-pointer -o strings -O0 strings.c

sharedReturn.o: sharedReturn.c
	gcc -m64 -fno-pic -no-pie -fno-omit-frame-pointer -fno-inline -o sharedReturn.o -O2 -c sharedReturn.c

# A PE for x86-64 from a MinGW clang toolchain. Each import gets a "jmp [IAT]" thunk.
import-args.exe: import-args.c import-args.h import-args.def
	llvm-dlltool -m i386:x86-64 -d import-args.def -l libimport-args-api.a
	clang --target=x86_64-w64-windows-gnu -O1 -fno-builtin -fno-optimize-sibling-calls -nostdlib -Wl,-e,probe_main -o import-args.exe import-args.c -L. -limport-args-api -lmsvcrt-os
	rm -f libimport-args-api.a

# The same toolchain. The imports have the dllimport attribute, so each call is a "call [IAT]".
import-direct.exe: import-direct.c import-args.def
	llvm-dlltool -m i386:x86-64 -d import-args.def -l libimport-args-api.a
	clang --target=x86_64-w64-windows-gnu -O1 -fno-builtin -fno-optimize-sibling-calls -nostdlib -Wl,-e,direct_main -o import-direct.exe import-direct.c -L. -limport-args-api -lmsvcrt-os -lkernel32
	rm -f libimport-args-api.a

# A PE for x86 with 32 bits. The import library has stdcall and cdecl functions.
import-direct32.exe: import-direct32.c import-direct32.def
	llvm-dlltool -m i386 -k -d import-direct32.def -l libimport-direct32-api.a
	clang --target=i686-w64-windows-gnu -O1 -fno-builtin -fno-optimize-sibling-calls -nostdlib -Wl,-e,_direct_main -o import-direct32.exe import-direct32.c -L. -limport-direct32-api
	rm -f libimport-direct32-api.a

# A PE for x86-64 with thunks. One import has a signature without args, and one has no signature.
import-noargs.exe: import-noargs.c import-noargs.def
	llvm-dlltool -m i386:x86-64 -d import-noargs.def -l libimport-noargs-api.a
	clang --target=x86_64-w64-windows-gnu -O1 -fno-builtin -fno-optimize-sibling-calls -nostdlib -Wl,-e,noargs_main -o import-noargs.exe import-noargs.c -L. -limport-noargs-api -lkernel32
	rm -f libimport-noargs-api.a

# Two PE files for x86 with 32 bits. The imports return a 64-bit integer, a double, a float, a structure and nothing.
# The first file has a thunk for each import. The second file calls each import through its slot.
import-return32.exe: import-return32.c import-return32.def
	llvm-dlltool -m i386 -d import-return32.def -l libimport-return32-api.a
	clang --target=i686-w64-windows-gnu -O1 -fno-builtin -fno-optimize-sibling-calls -nostdlib -Wl,-e,_return_main -o import-return32.exe import-return32.c -L. -limport-return32-api
	rm -f libimport-return32-api.a

import-return32-slot.exe: import-return32.c import-return32.def
	llvm-dlltool -m i386 -d import-return32.def -l libimport-return32-api.a
	clang --target=i686-w64-windows-gnu -O1 -fno-builtin -fno-optimize-sibling-calls -nostdlib -Wl,-e,_return_main -DUSE_SLOTS -o import-return32-slot.exe import-return32.c -L. -limport-return32-api
	rm -f libimport-return32-api.a

# An ELF object file for x86-64. Each call of an import has a reloc.
import-reloc.o: import-reloc.c
	clang --target=x86_64-unknown-linux-gnu -O1 -fno-builtin -fno-optimize-sibling-calls -fno-pic -c -o import-reloc.o import-reloc.c

# A PE for x86-64 with pointers to short strings and to other data.
pointer-string.exe: pointer-string.c
	clang --target=x86_64-w64-windows-gnu -O1 -fno-builtin -fno-optimize-sibling-calls -nostdlib -Wl,-e,pointer_main -o pointer-string.exe pointer-string.c -lmsvcrt-os

# A PE for x86-64 with pointers to functions and to a label in a function.
callback-flag.exe: callback-flag.c
	clang --target=x86_64-w64-windows-gnu -O1 -fno-builtin -fno-optimize-sibling-calls -nostdlib -Wl,-e,callback_main -o callback-flag.exe callback-flag.c -lmsvcrt-os

# Two PE files for x86-64 with DWARF data for structures. The first file has the default DWARF version.
# The second file has DWARF 2, where the offset of a structure member is a location expression.
struct-offset.exe: struct-offset.c
	clang --target=x86_64-w64-windows-gnu -O1 -g -fno-builtin -fno-optimize-sibling-calls -nostdlib -Wl,-e,struct_main -o struct-offset.exe struct-offset.c

struct-offset-dwarf2.exe: struct-offset.c
	clang --target=x86_64-w64-windows-gnu -O1 -g -gdwarf-2 -fno-builtin -fno-optimize-sibling-calls -nostdlib -Wl,-e,struct_main -o struct-offset-dwarf2.exe struct-offset.c

# A PE for x86-64 with DWARF 5 data. A structure has an array of structures and then one more member.
struct-table.exe: struct-table.c
	clang --target=x86_64-w64-windows-gnu -O1 -g -gdwarf-5 -fno-optimize-sibling-calls -nostdlib -Wl,-e,ReviewEntry -o struct-table.exe struct-table.c

# Two PE files for x86-64 with DWARF 5 data and DWARF 2 data. A structure has an array with two dimensions and then one more member.
struct-matrix.exe: struct-matrix.c
	clang --target=x86_64-w64-windows-gnu -O1 -g -gdwarf-5 -fno-optimize-sibling-calls -nostdlib -Wl,-e,ReviewEntry -o struct-matrix.exe struct-matrix.c

struct-matrix-dwarf2.exe: struct-matrix.c
	clang --target=x86_64-w64-windows-gnu -O1 -g -gdwarf-2 -fno-optimize-sibling-calls -nostdlib -Wl,-e,ReviewEntry -o struct-matrix-dwarf2.exe struct-matrix.c

# A PE for x86-64 with DWARF 2 data. The location of three structure members is "DW_OP_lit<n>, DW_OP_plus".
# The compiler writes "DW_OP_plus_uconst <n>" for these members. The file struct-location.s is the output of
# the command below, and then a person changed the three locations in it.
# clang --target=x86_64-w64-windows-gnu -O1 -g -gdwarf-2 -fno-optimize-sibling-calls -fdebug-compilation-dir=. -S -o struct-location.s struct-location.c
struct-location.exe: struct-location.s
	clang --target=x86_64-w64-windows-gnu -nostdlib -Wl,-e,LocationEntry -o struct-location.exe struct-location.s

# A PE for x86-64 with the PDB file pdb-array.pdb. Three structures have an array and then one more member.
# The arrays are an array of structures, an array with two dimensions and a wchar_t array.
# One more structure has a char8_t array. Rizin has no size for this element type in a PDB file.
pdb-array.exe: pdb-array.cpp
	clang --target=x86_64-pc-windows-msvc -std=c++20 -O1 -g -gcodeview -fno-builtin -fno-optimize-sibling-calls -fno-exceptions -fno-rtti -nostdlib -fuse-ld=lld -Wl,/entry:PdbArrayEntry,/debug,/pdb:pdb-array.pdb,/pdbaltpath:pdb-array.pdb,/nodefaultlib,/subsystem:console -o pdb-array.exe pdb-array.cpp

# A PE for x86-64 with DWARF 5 data. Two global arrays have structures as elements.
# The compiler puts two bytes between the two members of each structure.
struct-global.exe: struct-global.c
	clang --target=x86_64-w64-windows-gnu -O1 -g -gdwarf-5 -fno-optimize-sibling-calls -nostdlib -Wl,-e,GlobalEntry -o struct-global.exe struct-global.c

# A PE for x86-64. A string starts in a read-only section and continues in a writable section.
string-boundary.exe: string-boundary.s
	clang --target=x86_64-w64-windows-gnu -nostdlib -Wl,-e,ProbeBoundary -Wl,--export-all-symbols -o string-boundary.exe string-boundary.s -lmsvcrt-os

# A PE for x86-64 with one string in a writable section and one string in a read-only section.
writable-string.exe: writable-string.c
	clang --target=x86_64-w64-windows-gnu -O1 -fno-builtin -fno-optimize-sibling-calls -nostdlib -Wl,-e,writable_main -o writable-string.exe writable-string.c -lmsvcrt-os

# A PE for x86-64. The callers give the address of a small local and small values to functions of the same file.
callee-arg-width.exe: callee-arg-width.c
	clang --target=x86_64-w64-windows-gnu -O1 -fno-builtin -fno-optimize-sibling-calls -nostdlib -Wl,-e,width_main -o callee-arg-width.exe callee-arg-width.c -lmsvcrt-os
