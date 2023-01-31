

.section .text, "ax"
.globl _start
_start:
	int $0x80
	jmp .
