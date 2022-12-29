#define __ASSEMBLY__
#include <asm/memmap.h>
#include <asm/page.h>

.extern on_boot
.extern kmain
.extern cpu_die
.extern gdt

/* page directory */
.extern __kpd
/* first page table (maps 4 MiB)*/
.extern __kpt

/*
code is loaded to LOAD_PHYS_ADDR,
We must enable paging, so that

   VIRTUAL	  ->	PHYSICAL
   0xc0000000     ->	0x00000000

Kernel is loaded on physical address PHYS_LOAD_ADDR by bootloader
	(see asm/memmap.h)
*/
.section .text
.globl _start
_start:
	cli
	/* cleanup page directory */
	hlt
	jmp kmain
	/* die if kmain returns */
	jmp cpu_die
