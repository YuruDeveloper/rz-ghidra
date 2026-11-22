# A string that starts at the last byte of a read-only section and continues in a writable section.
# Build with the string-boundary.exe rule in the Makefile. The program is not made to run.
# ProbeBoundary writes the letter C on the letter B and then gives the string to puts.
.text
.globl ProbeBoundary, ProbeWritable, ProbeOverlap
ProbeBoundary:
  subq $40, %rsp
  movb $67, Tail(%rip)
  leaq Head(%rip), %rcx
  call puts
  addq $40, %rsp
  ret
ProbeWritable:
  subq $40, %rsp
  movb $68, Tail(%rip)
  leaq Tail(%rip), %rcx
  call puts
  addq $40, %rsp
  ret
ProbeOverlap:
  movzwl Head(%rip), %eax
  ret
.section .xhead,"dr"
  .space 4095,0
Head:
  .byte 65
.section .ytail,"dw"
Tail:
  .byte 66,0
