#include "multiboot.h"

.section .multiboot

#define MLTB1_FLAGS (MLTB1_PAGING | MLTB1_MEMINFO)
multiboot_header_start:

.long MLTB1_MAGIC
.long MLTB1_FLAGS
.long -(MLTB1_FLAGS + MLTB1_MAGIC)

multiboot_header_end:

.section .text
.globl _start
_start:

.extern kmain
	cli
	jmp kmain

_dead:
	hlt
	jmp _dead
