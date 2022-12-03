#include <asm/memmap.h>

/* define memory symbols for multiboot.ld */

.globl __conv_mem_start_addr
.globl __conv_mem_len 
.globl __conv_mem_end_addr

__conv_mem_start_addr = FREE_MEM_ADDR
__conv_mem_len = FREE_MEM_LEN
__conv_mem_end_addr = (__conv_mem_start_addr + __conv_mem_len)

.extern on_boot

.section .text
.globl _start
_start:
	cli
	jmp on_boot

_dead:
	hlt
	jmp _dead
