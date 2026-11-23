# The compiler made this file from struct-location.c with DWARF 2 data. The Makefile shows the command.
# After that, the location of three structure members changed from "DW_OP_plus_uconst <n>" to "DW_OP_lit<n>, DW_OP_plus".
# The members are MixedValue in LocationMixed, GapLast in LocationGap and TightSecond in LocationTight.
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
@feat.00 = 0
	.file	"struct-location.c"
	.file	1 "." "struct-location.c"
	.def	SetMixed;
	.scl	2;
	.type	32;
	.endef
	.text
	.globl	SetMixed                        # -- Begin function SetMixed
	.p2align	4
SetMixed:                               # @SetMixed
.Lfunc_begin0:
# %bb.0:
	#DEBUG_VALUE: SetMixed:mixed <- $rcx
	#DEBUG_VALUE: SetMixed:value <- $edx
	.loc	1 40 21 prologue_end            # struct-location.c:40:21
	movl	%edx, 4(%rcx)
	.loc	1 41 1                          # struct-location.c:41:1
	retq
.Ltmp0:
.Lfunc_end0:
                                        # -- End function
	.def	SetGap;
	.scl	2;
	.type	32;
	.endef
	.globl	SetGap                          # -- Begin function SetGap
	.p2align	4
SetGap:                                 # @SetGap
.Lfunc_begin1:
# %bb.0:
	#DEBUG_VALUE: SetGap:gap <- $rcx
	#DEBUG_VALUE: SetGap:value <- $edx
	.loc	1 45 17 prologue_end            # struct-location.c:45:17
	movl	%edx, 4(%rcx)
	.loc	1 46 16                         # struct-location.c:46:16
	movl	%edx, 8(%rcx)
	.loc	1 47 1                          # struct-location.c:47:1
	retq
.Ltmp1:
.Lfunc_end1:
                                        # -- End function
	.def	SetTight;
	.scl	2;
	.type	32;
	.endef
	.globl	SetTight                        # -- Begin function SetTight
	.p2align	4
SetTight:                               # @SetTight
.Lfunc_begin2:
# %bb.0:
	#DEBUG_VALUE: SetTight:tight <- $rcx
	#DEBUG_VALUE: SetTight:value <- $edx
	.loc	1 51 22 prologue_end            # struct-location.c:51:22
	movl	%edx, 4(%rcx)
	.loc	1 52 16                         # struct-location.c:52:16
	movl	%edx, 8(%rcx)
	.loc	1 53 1                          # struct-location.c:53:1
	retq
.Ltmp2:
.Lfunc_end2:
                                        # -- End function
	.def	SetOuter;
	.scl	2;
	.type	32;
	.endef
	.globl	SetOuter                        # -- Begin function SetOuter
	.p2align	4
SetOuter:                               # @SetOuter
.Lfunc_begin3:
# %bb.0:
	#DEBUG_VALUE: SetOuter:outer <- $rcx
	#DEBUG_VALUE: SetOuter:value <- $edx
	.loc	1 57 27 prologue_end            # struct-location.c:57:27
	movl	%edx, 8(%rcx)
	.loc	1 58 15                         # struct-location.c:58:15
	movl	%edx, 12(%rcx)
	.loc	1 59 1                          # struct-location.c:59:1
	retq
.Ltmp3:
.Lfunc_end3:
                                        # -- End function
	.def	SetMixes;
	.scl	2;
	.type	32;
	.endef
	.globl	SetMixes                        # -- Begin function SetMixes
	.p2align	4
SetMixes:                               # @SetMixes
.Lfunc_begin4:
# %bb.0:
	#DEBUG_VALUE: SetMixes:value <- $ecx
	.loc	1 62 23 prologue_end            # struct-location.c:62:23
	movl	%ecx, Mixes+12(%rip)
	.loc	1 63 14                         # struct-location.c:63:14
	movl	%ecx, AfterMixes(%rip)
	.loc	1 64 1                          # struct-location.c:64:1
	retq
.Ltmp4:
.Lfunc_end4:
                                        # -- End function
	.def	LocationEntry;
	.scl	2;
	.type	32;
	.endef
	.globl	LocationEntry                   # -- Begin function LocationEntry
	.p2align	4
LocationEntry:                          # @LocationEntry
.Lfunc_begin5:
	.loc	1 66 0                          # struct-location.c:66:0
.seh_proc LocationEntry
# %bb.0:
	#DEBUG_VALUE: LocationEntry:memory <- $rcx
	#DEBUG_VALUE: LocationEntry:value <- $edx
	pushq	%rsi
	.seh_pushreg %rsi
	pushq	%rdi
	.seh_pushreg %rdi
	subq	$40, %rsp
	.seh_stackalloc 40
	.seh_endprologue
	movl	%edx, %esi
	movq	%rcx, %rdi
.Ltmp5:
	.loc	1 67 3 prologue_end             # struct-location.c:67:3
	callq	SetMixed
.Ltmp6:
	#DEBUG_VALUE: LocationEntry:value <- $esi
	#DEBUG_VALUE: LocationEntry:memory <- $rdi
	.loc	1 68 3                          # struct-location.c:68:3
	movq	%rdi, %rcx
	movl	%esi, %edx
	callq	SetGap
	.loc	1 69 3                          # struct-location.c:69:3
	movq	%rdi, %rcx
	movl	%esi, %edx
	callq	SetTight
	.loc	1 70 3                          # struct-location.c:70:3
	movq	%rdi, %rcx
	movl	%esi, %edx
	callq	SetOuter
	.loc	1 71 3                          # struct-location.c:71:3
	movl	%esi, %ecx
	callq	SetMixes
	nop
	.seh_startepilogue
	.loc	1 72 1 epilogue_begin           # struct-location.c:72:1
	addq	$40, %rsp
	popq	%rdi
.Ltmp7:
	#DEBUG_VALUE: LocationEntry:memory <- [DW_OP_LLVM_entry_value 1] $rcx
	popq	%rsi
.Ltmp8:
	#DEBUG_VALUE: LocationEntry:value <- [DW_OP_LLVM_entry_value 1] $edx
	.seh_endepilogue
	retq
.Ltmp9:
.Lfunc_end5:
	.seh_endproc
                                        # -- End function
	.bss
	.globl	Mixes                           # @Mixes
	.p2align	4, 0x0
Mixes:
	.zero	16

	.globl	AfterMixes                      # @AfterMixes
	.p2align	2, 0x0
AfterMixes:
	.long	0                               # 0x0

	.section	.debug$S,"dr"
	.p2align	2, 0x0
	.long	4                               # Debug section magic
	.long	241
	.long	.Ltmp11-.Ltmp10                 # Subsection size
.Ltmp10:
	.short	.Ltmp13-.Ltmp12                 # Record length
.Ltmp12:
	.short	4353                            # Record kind: S_OBJNAME
	.long	0                               # Signature
	.byte	0                               # Object name
	.p2align	2, 0x0
.Ltmp13:
	.short	.Ltmp15-.Ltmp14                 # Record length
.Ltmp14:
	.short	4412                            # Record kind: S_COMPILE3
	.long	0                               # Flags and language
	.short	208                             # CPUType
	.short	22                              # Frontend version
	.short	1
	.short	8
	.short	0
	.short	22018                           # Backend version
	.short	0
	.short	0
	.short	0
	.asciz	"clang version 22.1.8 (https://github.com/msys2/MINGW-packages d34feaaa1d0aff624c870910b6f2589aa40d20de)" # Null-terminated compiler version string
	.p2align	2, 0x0
.Ltmp15:
.Ltmp11:
	.p2align	2, 0x0
	.section	.debug_loc,"dr"
.Ldebug_loc0:
	.quad	.Lfunc_begin5-.Lfunc_begin0
	.quad	.Ltmp6-.Lfunc_begin0
	.short	1                               # Loc expr size
	.byte	82                              # DW_OP_reg2
	.quad	.Ltmp6-.Lfunc_begin0
	.quad	.Ltmp7-.Lfunc_begin0
	.short	1                               # Loc expr size
	.byte	85                              # DW_OP_reg5
	.quad	.Ltmp7-.Lfunc_begin0
	.quad	.Lfunc_end5-.Lfunc_begin0
	.short	3                               # Loc expr size
	.byte	243                             # DW_OP_GNU_entry_value
	.byte	1                               # 1
	.byte	82                              # DW_OP_reg2
	.quad	0
	.quad	0
.Ldebug_loc1:
	.quad	.Lfunc_begin5-.Lfunc_begin0
	.quad	.Ltmp6-.Lfunc_begin0
	.short	1                               # Loc expr size
	.byte	81                              # super-register DW_OP_reg1
	.quad	.Ltmp6-.Lfunc_begin0
	.quad	.Ltmp8-.Lfunc_begin0
	.short	1                               # Loc expr size
	.byte	84                              # super-register DW_OP_reg4
	.quad	.Ltmp8-.Lfunc_begin0
	.quad	.Lfunc_end5-.Lfunc_begin0
	.short	3                               # Loc expr size
	.byte	243                             # DW_OP_GNU_entry_value
	.byte	1                               # 1
	.byte	81                              # super-register DW_OP_reg1
	.quad	0
	.quad	0
	.section	.debug_abbrev,"dr"
	.byte	1                               # Abbreviation Code
	.byte	17                              # DW_TAG_compile_unit
	.byte	1                               # DW_CHILDREN_yes
	.byte	37                              # DW_AT_producer
	.byte	14                              # DW_FORM_strp
	.byte	19                              # DW_AT_language
	.byte	5                               # DW_FORM_data2
	.byte	3                               # DW_AT_name
	.byte	14                              # DW_FORM_strp
	.byte	16                              # DW_AT_stmt_list
	.byte	6                               # DW_FORM_data4
	.byte	27                              # DW_AT_comp_dir
	.byte	14                              # DW_FORM_strp
	.byte	17                              # DW_AT_low_pc
	.byte	1                               # DW_FORM_addr
	.byte	18                              # DW_AT_high_pc
	.byte	1                               # DW_FORM_addr
	.byte	0                               # EOM(1)
	.byte	0                               # EOM(2)
	.byte	2                               # Abbreviation Code
	.byte	52                              # DW_TAG_variable
	.byte	0                               # DW_CHILDREN_no
	.byte	3                               # DW_AT_name
	.byte	14                              # DW_FORM_strp
	.byte	73                              # DW_AT_type
	.byte	19                              # DW_FORM_ref4
	.byte	63                              # DW_AT_external
	.byte	12                              # DW_FORM_flag
	.byte	58                              # DW_AT_decl_file
	.byte	11                              # DW_FORM_data1
	.byte	59                              # DW_AT_decl_line
	.byte	11                              # DW_FORM_data1
	.byte	2                               # DW_AT_location
	.byte	10                              # DW_FORM_block1
	.byte	0                               # EOM(1)
	.byte	0                               # EOM(2)
	.byte	3                               # Abbreviation Code
	.byte	1                               # DW_TAG_array_type
	.byte	1                               # DW_CHILDREN_yes
	.byte	73                              # DW_AT_type
	.byte	19                              # DW_FORM_ref4
	.byte	0                               # EOM(1)
	.byte	0                               # EOM(2)
	.byte	4                               # Abbreviation Code
	.byte	33                              # DW_TAG_subrange_type
	.byte	0                               # DW_CHILDREN_no
	.byte	73                              # DW_AT_type
	.byte	19                              # DW_FORM_ref4
	.byte	55                              # DW_AT_count
	.byte	11                              # DW_FORM_data1
	.byte	0                               # EOM(1)
	.byte	0                               # EOM(2)
	.byte	5                               # Abbreviation Code
	.byte	19                              # DW_TAG_structure_type
	.byte	1                               # DW_CHILDREN_yes
	.byte	3                               # DW_AT_name
	.byte	14                              # DW_FORM_strp
	.byte	11                              # DW_AT_byte_size
	.byte	11                              # DW_FORM_data1
	.byte	58                              # DW_AT_decl_file
	.byte	11                              # DW_FORM_data1
	.byte	59                              # DW_AT_decl_line
	.byte	11                              # DW_FORM_data1
	.byte	0                               # EOM(1)
	.byte	0                               # EOM(2)
	.byte	6                               # Abbreviation Code
	.byte	13                              # DW_TAG_member
	.byte	0                               # DW_CHILDREN_no
	.byte	3                               # DW_AT_name
	.byte	14                              # DW_FORM_strp
	.byte	73                              # DW_AT_type
	.byte	19                              # DW_FORM_ref4
	.byte	58                              # DW_AT_decl_file
	.byte	11                              # DW_FORM_data1
	.byte	59                              # DW_AT_decl_line
	.byte	11                              # DW_FORM_data1
	.byte	11                              # DW_AT_byte_size
	.byte	11                              # DW_FORM_data1
	.byte	13                              # DW_AT_bit_size
	.byte	11                              # DW_FORM_data1
	.byte	12                              # DW_AT_bit_offset
	.byte	11                              # DW_FORM_data1
	.byte	56                              # DW_AT_data_member_location
	.byte	10                              # DW_FORM_block1
	.byte	0                               # EOM(1)
	.byte	0                               # EOM(2)
	.byte	7                               # Abbreviation Code
	.byte	13                              # DW_TAG_member
	.byte	0                               # DW_CHILDREN_no
	.byte	3                               # DW_AT_name
	.byte	14                              # DW_FORM_strp
	.byte	73                              # DW_AT_type
	.byte	19                              # DW_FORM_ref4
	.byte	58                              # DW_AT_decl_file
	.byte	11                              # DW_FORM_data1
	.byte	59                              # DW_AT_decl_line
	.byte	11                              # DW_FORM_data1
	.byte	56                              # DW_AT_data_member_location
	.byte	10                              # DW_FORM_block1
	.byte	0                               # EOM(1)
	.byte	0                               # EOM(2)
	.byte	8                               # Abbreviation Code
	.byte	36                              # DW_TAG_base_type
	.byte	0                               # DW_CHILDREN_no
	.byte	3                               # DW_AT_name
	.byte	14                              # DW_FORM_strp
	.byte	62                              # DW_AT_encoding
	.byte	11                              # DW_FORM_data1
	.byte	11                              # DW_AT_byte_size
	.byte	11                              # DW_FORM_data1
	.byte	0                               # EOM(1)
	.byte	0                               # EOM(2)
	.byte	9                               # Abbreviation Code
	.byte	36                              # DW_TAG_base_type
	.byte	0                               # DW_CHILDREN_no
	.byte	3                               # DW_AT_name
	.byte	14                              # DW_FORM_strp
	.byte	11                              # DW_AT_byte_size
	.byte	11                              # DW_FORM_data1
	.byte	62                              # DW_AT_encoding
	.byte	11                              # DW_FORM_data1
	.byte	0                               # EOM(1)
	.byte	0                               # EOM(2)
	.byte	10                              # Abbreviation Code
	.byte	46                              # DW_TAG_subprogram
	.byte	1                               # DW_CHILDREN_yes
	.byte	17                              # DW_AT_low_pc
	.byte	1                               # DW_FORM_addr
	.byte	18                              # DW_AT_high_pc
	.byte	1                               # DW_FORM_addr
	.byte	64                              # DW_AT_frame_base
	.byte	10                              # DW_FORM_block1
	.byte	3                               # DW_AT_name
	.byte	14                              # DW_FORM_strp
	.byte	58                              # DW_AT_decl_file
	.byte	11                              # DW_FORM_data1
	.byte	59                              # DW_AT_decl_line
	.byte	11                              # DW_FORM_data1
	.byte	39                              # DW_AT_prototyped
	.byte	12                              # DW_FORM_flag
	.byte	63                              # DW_AT_external
	.byte	12                              # DW_FORM_flag
	.byte	0                               # EOM(1)
	.byte	0                               # EOM(2)
	.byte	11                              # Abbreviation Code
	.byte	5                               # DW_TAG_formal_parameter
	.byte	0                               # DW_CHILDREN_no
	.byte	2                               # DW_AT_location
	.byte	10                              # DW_FORM_block1
	.byte	3                               # DW_AT_name
	.byte	14                              # DW_FORM_strp
	.byte	58                              # DW_AT_decl_file
	.byte	11                              # DW_FORM_data1
	.byte	59                              # DW_AT_decl_line
	.byte	11                              # DW_FORM_data1
	.byte	73                              # DW_AT_type
	.byte	19                              # DW_FORM_ref4
	.byte	0                               # EOM(1)
	.byte	0                               # EOM(2)
	.byte	12                              # Abbreviation Code
	.byte	5                               # DW_TAG_formal_parameter
	.byte	0                               # DW_CHILDREN_no
	.byte	2                               # DW_AT_location
	.byte	6                               # DW_FORM_data4
	.byte	3                               # DW_AT_name
	.byte	14                              # DW_FORM_strp
	.byte	58                              # DW_AT_decl_file
	.byte	11                              # DW_FORM_data1
	.byte	59                              # DW_AT_decl_line
	.byte	11                              # DW_FORM_data1
	.byte	73                              # DW_AT_type
	.byte	19                              # DW_FORM_ref4
	.byte	0                               # EOM(1)
	.byte	0                               # EOM(2)
	.byte	13                              # Abbreviation Code
	.byte	15                              # DW_TAG_pointer_type
	.byte	0                               # DW_CHILDREN_no
	.byte	73                              # DW_AT_type
	.byte	19                              # DW_FORM_ref4
	.byte	0                               # EOM(1)
	.byte	0                               # EOM(2)
	.byte	14                              # Abbreviation Code
	.byte	15                              # DW_TAG_pointer_type
	.byte	0                               # DW_CHILDREN_no
	.byte	0                               # EOM(1)
	.byte	0                               # EOM(2)
	.byte	0                               # EOM(3)
	.section	.debug_info,"dr"
.Lcu_begin0:
	.long	.Ldebug_info_end0-.Ldebug_info_start0 # Length of Unit
.Ldebug_info_start0:
	.short	2                               # DWARF version number
	.secrel32	.debug_abbrev           # Offset Into Abbrev. Section
	.byte	8                               # Address Size (in bytes)
	.byte	1                               # Abbrev [1] 0xb:0x282 DW_TAG_compile_unit
	.secrel32	.Linfo_string0          # DW_AT_producer
	.short	29                              # DW_AT_language
	.secrel32	.Linfo_string1          # DW_AT_name
	.secrel32	.Lline_table_start0     # DW_AT_stmt_list
	.secrel32	.Linfo_string2          # DW_AT_comp_dir
	.quad	.Lfunc_begin0                   # DW_AT_low_pc
	.quad	.Lfunc_end5                     # DW_AT_high_pc
	.byte	2                               # Abbrev [2] 0x2e:0x16 DW_TAG_variable
	.secrel32	.Linfo_string3          # DW_AT_name
	.long	68                              # DW_AT_type
	.byte	1                               # DW_AT_external
	.byte	1                               # DW_AT_decl_file
	.byte	35                              # DW_AT_decl_line
	.byte	9                               # DW_AT_location
	.byte	3
	.quad	Mixes
	.byte	3                               # Abbrev [3] 0x44:0xc DW_TAG_array_type
	.long	80                              # DW_AT_type
	.byte	4                               # Abbrev [4] 0x49:0x6 DW_TAG_subrange_type
	.long	127                             # DW_AT_type
	.byte	2                               # DW_AT_count
	.byte	0                               # End Of Children Mark
	.byte	5                               # Abbrev [5] 0x50:0x28 DW_TAG_structure_type
	.secrel32	.Linfo_string7          # DW_AT_name
	.byte	8                               # DW_AT_byte_size
	.byte	1                               # DW_AT_decl_file
	.byte	4                               # DW_AT_decl_line
	.byte	6                               # Abbrev [6] 0x58:0x11 DW_TAG_member
	.secrel32	.Linfo_string4          # DW_AT_name
	.long	120                             # DW_AT_type
	.byte	1                               # DW_AT_decl_file
	.byte	5                               # DW_AT_decl_line
	.byte	4                               # DW_AT_byte_size
	.byte	32                              # DW_AT_bit_size
	.byte	0                               # DW_AT_bit_offset
	.byte	2                               # DW_AT_data_member_location
	.byte	35
	.byte	0
	.byte	7                               # Abbrev [7] 0x69:0xe DW_TAG_member
	.secrel32	.Linfo_string6          # DW_AT_name
	.long	120                             # DW_AT_type
	.byte	1                               # DW_AT_decl_file
	.byte	6                               # DW_AT_decl_line
	.byte	2                               # DW_AT_data_member_location
	.byte	52                              # DW_OP_lit4
	.byte	34                              # DW_OP_plus
	.byte	0                               # End Of Children Mark
	.byte	8                               # Abbrev [8] 0x78:0x7 DW_TAG_base_type
	.secrel32	.Linfo_string5          # DW_AT_name
	.byte	7                               # DW_AT_encoding
	.byte	4                               # DW_AT_byte_size
	.byte	9                               # Abbrev [9] 0x7f:0x7 DW_TAG_base_type
	.secrel32	.Linfo_string8          # DW_AT_name
	.byte	8                               # DW_AT_byte_size
	.byte	7                               # DW_AT_encoding
	.byte	2                               # Abbrev [2] 0x86:0x16 DW_TAG_variable
	.secrel32	.Linfo_string9          # DW_AT_name
	.long	120                             # DW_AT_type
	.byte	1                               # DW_AT_external
	.byte	1                               # DW_AT_decl_file
	.byte	36                              # DW_AT_decl_line
	.byte	9                               # DW_AT_location
	.byte	3
	.quad	AfterMixes
	.byte	10                              # Abbrev [10] 0x9c:0x36 DW_TAG_subprogram
	.quad	.Lfunc_begin0                   # DW_AT_low_pc
	.quad	.Lfunc_end0                     # DW_AT_high_pc
	.byte	1                               # DW_AT_frame_base
	.byte	87
	.secrel32	.Linfo_string10         # DW_AT_name
	.byte	1                               # DW_AT_decl_file
	.byte	38                              # DW_AT_decl_line
	.byte	1                               # DW_AT_prototyped
	.byte	1                               # DW_AT_external
	.byte	11                              # Abbrev [11] 0xb7:0xd DW_TAG_formal_parameter
	.byte	1                               # DW_AT_location
	.byte	82
	.secrel32	.Linfo_string16         # DW_AT_name
	.byte	1                               # DW_AT_decl_file
	.byte	38                              # DW_AT_decl_line
	.long	471                             # DW_AT_type
	.byte	11                              # Abbrev [11] 0xc4:0xd DW_TAG_formal_parameter
	.byte	1                               # DW_AT_location
	.byte	81
	.secrel32	.Linfo_string17         # DW_AT_name
	.byte	1                               # DW_AT_decl_file
	.byte	39                              # DW_AT_decl_line
	.long	120                             # DW_AT_type
	.byte	0                               # End Of Children Mark
	.byte	10                              # Abbrev [10] 0xd2:0x36 DW_TAG_subprogram
	.quad	.Lfunc_begin1                   # DW_AT_low_pc
	.quad	.Lfunc_end1                     # DW_AT_high_pc
	.byte	1                               # DW_AT_frame_base
	.byte	87
	.secrel32	.Linfo_string11         # DW_AT_name
	.byte	1                               # DW_AT_decl_file
	.byte	43                              # DW_AT_decl_line
	.byte	1                               # DW_AT_prototyped
	.byte	1                               # DW_AT_external
	.byte	11                              # Abbrev [11] 0xed:0xd DW_TAG_formal_parameter
	.byte	1                               # DW_AT_location
	.byte	82
	.secrel32	.Linfo_string18         # DW_AT_name
	.byte	1                               # DW_AT_decl_file
	.byte	43                              # DW_AT_decl_line
	.long	476                             # DW_AT_type
	.byte	11                              # Abbrev [11] 0xfa:0xd DW_TAG_formal_parameter
	.byte	1                               # DW_AT_location
	.byte	81
	.secrel32	.Linfo_string17         # DW_AT_name
	.byte	1                               # DW_AT_decl_file
	.byte	44                              # DW_AT_decl_line
	.long	120                             # DW_AT_type
	.byte	0                               # End Of Children Mark
	.byte	10                              # Abbrev [10] 0x108:0x36 DW_TAG_subprogram
	.quad	.Lfunc_begin2                   # DW_AT_low_pc
	.quad	.Lfunc_end2                     # DW_AT_high_pc
	.byte	1                               # DW_AT_frame_base
	.byte	87
	.secrel32	.Linfo_string12         # DW_AT_name
	.byte	1                               # DW_AT_decl_file
	.byte	49                              # DW_AT_decl_line
	.byte	1                               # DW_AT_prototyped
	.byte	1                               # DW_AT_external
	.byte	11                              # Abbrev [11] 0x123:0xd DW_TAG_formal_parameter
	.byte	1                               # DW_AT_location
	.byte	82
	.secrel32	.Linfo_string24         # DW_AT_name
	.byte	1                               # DW_AT_decl_file
	.byte	49                              # DW_AT_decl_line
	.long	539                             # DW_AT_type
	.byte	11                              # Abbrev [11] 0x130:0xd DW_TAG_formal_parameter
	.byte	1                               # DW_AT_location
	.byte	81
	.secrel32	.Linfo_string17         # DW_AT_name
	.byte	1                               # DW_AT_decl_file
	.byte	50                              # DW_AT_decl_line
	.long	120                             # DW_AT_type
	.byte	0                               # End Of Children Mark
	.byte	10                              # Abbrev [10] 0x13e:0x36 DW_TAG_subprogram
	.quad	.Lfunc_begin3                   # DW_AT_low_pc
	.quad	.Lfunc_end3                     # DW_AT_high_pc
	.byte	1                               # DW_AT_frame_base
	.byte	87
	.secrel32	.Linfo_string13         # DW_AT_name
	.byte	1                               # DW_AT_decl_file
	.byte	55                              # DW_AT_decl_line
	.byte	1                               # DW_AT_prototyped
	.byte	1                               # DW_AT_external
	.byte	11                              # Abbrev [11] 0x159:0xd DW_TAG_formal_parameter
	.byte	1                               # DW_AT_location
	.byte	82
	.secrel32	.Linfo_string29         # DW_AT_name
	.byte	1                               # DW_AT_decl_file
	.byte	55                              # DW_AT_decl_line
	.long	595                             # DW_AT_type
	.byte	11                              # Abbrev [11] 0x166:0xd DW_TAG_formal_parameter
	.byte	1                               # DW_AT_location
	.byte	81
	.secrel32	.Linfo_string17         # DW_AT_name
	.byte	1                               # DW_AT_decl_file
	.byte	56                              # DW_AT_decl_line
	.long	120                             # DW_AT_type
	.byte	0                               # End Of Children Mark
	.byte	10                              # Abbrev [10] 0x174:0x29 DW_TAG_subprogram
	.quad	.Lfunc_begin4                   # DW_AT_low_pc
	.quad	.Lfunc_end4                     # DW_AT_high_pc
	.byte	1                               # DW_AT_frame_base
	.byte	87
	.secrel32	.Linfo_string14         # DW_AT_name
	.byte	1                               # DW_AT_decl_file
	.byte	61                              # DW_AT_decl_line
	.byte	1                               # DW_AT_prototyped
	.byte	1                               # DW_AT_external
	.byte	11                              # Abbrev [11] 0x18f:0xd DW_TAG_formal_parameter
	.byte	1                               # DW_AT_location
	.byte	82
	.secrel32	.Linfo_string17         # DW_AT_name
	.byte	1                               # DW_AT_decl_file
	.byte	61                              # DW_AT_decl_line
	.long	120                             # DW_AT_type
	.byte	0                               # End Of Children Mark
	.byte	10                              # Abbrev [10] 0x19d:0x3a DW_TAG_subprogram
	.quad	.Lfunc_begin5                   # DW_AT_low_pc
	.quad	.Lfunc_end5                     # DW_AT_high_pc
	.byte	1                               # DW_AT_frame_base
	.byte	87
	.secrel32	.Linfo_string15         # DW_AT_name
	.byte	1                               # DW_AT_decl_file
	.byte	66                              # DW_AT_decl_line
	.byte	1                               # DW_AT_prototyped
	.byte	1                               # DW_AT_external
	.byte	12                              # Abbrev [12] 0x1b8:0xf DW_TAG_formal_parameter
	.secrel32	.Ldebug_loc0            # DW_AT_location
	.secrel32	.Linfo_string34         # DW_AT_name
	.byte	1                               # DW_AT_decl_file
	.byte	66                              # DW_AT_decl_line
	.long	651                             # DW_AT_type
	.byte	12                              # Abbrev [12] 0x1c7:0xf DW_TAG_formal_parameter
	.secrel32	.Ldebug_loc1            # DW_AT_location
	.secrel32	.Linfo_string17         # DW_AT_name
	.byte	1                               # DW_AT_decl_file
	.byte	66                              # DW_AT_decl_line
	.long	120                             # DW_AT_type
	.byte	0                               # End Of Children Mark
	.byte	13                              # Abbrev [13] 0x1d7:0x5 DW_TAG_pointer_type
	.long	80                              # DW_AT_type
	.byte	13                              # Abbrev [13] 0x1dc:0x5 DW_TAG_pointer_type
	.long	481                             # DW_AT_type
	.byte	5                               # Abbrev [5] 0x1e1:0x33 DW_TAG_structure_type
	.secrel32	.Linfo_string23         # DW_AT_name
	.byte	12                              # DW_AT_byte_size
	.byte	1                               # DW_AT_decl_file
	.byte	9                               # DW_AT_decl_line
	.byte	7                               # Abbrev [7] 0x1e9:0xe DW_TAG_member
	.secrel32	.Linfo_string19         # DW_AT_name
	.long	532                             # DW_AT_type
	.byte	1                               # DW_AT_decl_file
	.byte	10                              # DW_AT_decl_line
	.byte	2                               # DW_AT_data_member_location
	.byte	35
	.byte	0
	.byte	7                               # Abbrev [7] 0x1f7:0xe DW_TAG_member
	.secrel32	.Linfo_string21         # DW_AT_name
	.long	120                             # DW_AT_type
	.byte	1                               # DW_AT_decl_file
	.byte	11                              # DW_AT_decl_line
	.byte	2                               # DW_AT_data_member_location
	.byte	35
	.byte	4
	.byte	7                               # Abbrev [7] 0x205:0xe DW_TAG_member
	.secrel32	.Linfo_string22         # DW_AT_name
	.long	120                             # DW_AT_type
	.byte	1                               # DW_AT_decl_file
	.byte	12                              # DW_AT_decl_line
	.byte	2                               # DW_AT_data_member_location
	.byte	56                              # DW_OP_lit8
	.byte	34                              # DW_OP_plus
	.byte	0                               # End Of Children Mark
	.byte	8                               # Abbrev [8] 0x214:0x7 DW_TAG_base_type
	.secrel32	.Linfo_string20         # DW_AT_name
	.byte	8                               # DW_AT_encoding
	.byte	1                               # DW_AT_byte_size
	.byte	13                              # Abbrev [13] 0x21b:0x5 DW_TAG_pointer_type
	.long	544                             # DW_AT_type
	.byte	5                               # Abbrev [5] 0x220:0x33 DW_TAG_structure_type
	.secrel32	.Linfo_string28         # DW_AT_name
	.byte	12                              # DW_AT_byte_size
	.byte	1                               # DW_AT_decl_file
	.byte	15                              # DW_AT_decl_line
	.byte	7                               # Abbrev [7] 0x228:0xe DW_TAG_member
	.secrel32	.Linfo_string25         # DW_AT_name
	.long	120                             # DW_AT_type
	.byte	1                               # DW_AT_decl_file
	.byte	16                              # DW_AT_decl_line
	.byte	2                               # DW_AT_data_member_location
	.byte	35
	.byte	0
	.byte	7                               # Abbrev [7] 0x236:0xe DW_TAG_member
	.secrel32	.Linfo_string26         # DW_AT_name
	.long	120                             # DW_AT_type
	.byte	1                               # DW_AT_decl_file
	.byte	17                              # DW_AT_decl_line
	.byte	2                               # DW_AT_data_member_location
	.byte	52                              # DW_OP_lit4
	.byte	34                              # DW_OP_plus
	.byte	7                               # Abbrev [7] 0x244:0xe DW_TAG_member
	.secrel32	.Linfo_string27         # DW_AT_name
	.long	120                             # DW_AT_type
	.byte	1                               # DW_AT_decl_file
	.byte	18                              # DW_AT_decl_line
	.byte	2                               # DW_AT_data_member_location
	.byte	35
	.byte	8
	.byte	0                               # End Of Children Mark
	.byte	13                              # Abbrev [13] 0x253:0x5 DW_TAG_pointer_type
	.long	600                             # DW_AT_type
	.byte	5                               # Abbrev [5] 0x258:0x33 DW_TAG_structure_type
	.secrel32	.Linfo_string33         # DW_AT_name
	.byte	16                              # DW_AT_byte_size
	.byte	1                               # DW_AT_decl_file
	.byte	21                              # DW_AT_decl_line
	.byte	7                               # Abbrev [7] 0x260:0xe DW_TAG_member
	.secrel32	.Linfo_string30         # DW_AT_name
	.long	532                             # DW_AT_type
	.byte	1                               # DW_AT_decl_file
	.byte	22                              # DW_AT_decl_line
	.byte	2                               # DW_AT_data_member_location
	.byte	35
	.byte	0
	.byte	7                               # Abbrev [7] 0x26e:0xe DW_TAG_member
	.secrel32	.Linfo_string31         # DW_AT_name
	.long	80                              # DW_AT_type
	.byte	1                               # DW_AT_decl_file
	.byte	23                              # DW_AT_decl_line
	.byte	2                               # DW_AT_data_member_location
	.byte	35
	.byte	4
	.byte	7                               # Abbrev [7] 0x27c:0xe DW_TAG_member
	.secrel32	.Linfo_string32         # DW_AT_name
	.long	120                             # DW_AT_type
	.byte	1                               # DW_AT_decl_file
	.byte	24                              # DW_AT_decl_line
	.byte	2                               # DW_AT_data_member_location
	.byte	35
	.byte	12
	.byte	0                               # End Of Children Mark
	.byte	14                              # Abbrev [14] 0x28b:0x1 DW_TAG_pointer_type
	.byte	0                               # End Of Children Mark
.Ldebug_info_end0:
	.section	.debug_str,"dr"
.Linfo_string0:
	.asciz	"clang version 22.1.8 (https://github.com/msys2/MINGW-packages d34feaaa1d0aff624c870910b6f2589aa40d20de)" # string offset=0
.Linfo_string1:
	.asciz	"struct-location.c"             # string offset=104
.Linfo_string2:
	.asciz	"."                             # string offset=122
.Linfo_string3:
	.asciz	"Mixes"                         # string offset=124
.Linfo_string4:
	.asciz	"Flags"                         # string offset=130
.Linfo_string5:
	.asciz	"unsigned int"                  # string offset=136
.Linfo_string6:
	.asciz	"MixedValue"                    # string offset=149
.Linfo_string7:
	.asciz	"LocationMixed"                 # string offset=160
.Linfo_string8:
	.asciz	"__ARRAY_SIZE_TYPE__"           # string offset=174
.Linfo_string9:
	.asciz	"AfterMixes"                    # string offset=194
.Linfo_string10:
	.asciz	"SetMixed"                      # string offset=205
.Linfo_string11:
	.asciz	"SetGap"                        # string offset=214
.Linfo_string12:
	.asciz	"SetTight"                      # string offset=221
.Linfo_string13:
	.asciz	"SetOuter"                      # string offset=230
.Linfo_string14:
	.asciz	"SetMixes"                      # string offset=239
.Linfo_string15:
	.asciz	"LocationEntry"                 # string offset=248
.Linfo_string16:
	.asciz	"mixed"                         # string offset=262
.Linfo_string17:
	.asciz	"value"                         # string offset=268
.Linfo_string18:
	.asciz	"gap"                           # string offset=274
.Linfo_string19:
	.asciz	"Tag"                           # string offset=278
.Linfo_string20:
	.asciz	"unsigned char"                 # string offset=282
.Linfo_string21:
	.asciz	"GapValue"                      # string offset=296
.Linfo_string22:
	.asciz	"GapLast"                       # string offset=305
.Linfo_string23:
	.asciz	"LocationGap"                   # string offset=313
.Linfo_string24:
	.asciz	"tight"                         # string offset=325
.Linfo_string25:
	.asciz	"First"                         # string offset=331
.Linfo_string26:
	.asciz	"TightSecond"                   # string offset=337
.Linfo_string27:
	.asciz	"Third"                         # string offset=349
.Linfo_string28:
	.asciz	"LocationTight"                 # string offset=355
.Linfo_string29:
	.asciz	"outer"                         # string offset=369
.Linfo_string30:
	.asciz	"Kind"                          # string offset=375
.Linfo_string31:
	.asciz	"Inner"                         # string offset=380
.Linfo_string32:
	.asciz	"Tail"                          # string offset=386
.Linfo_string33:
	.asciz	"LocationOuter"                 # string offset=391
.Linfo_string34:
	.asciz	"memory"                        # string offset=405
	.addrsig
	.section	.debug_line,"dr"
.Lline_table_start0:
