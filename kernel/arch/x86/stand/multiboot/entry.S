.section .text
.globl _start
_start:

.extern on_boot
	cli
	jmp on_boot

_dead:
	hlt
	jmp _dead
