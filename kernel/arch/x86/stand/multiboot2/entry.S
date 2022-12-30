#define __ASSEMBLY__

#include <asm/gdt.h>
#include <asm/memmap.h>
#include <asm/page.h>
#include <asm/cr.h>
#include <fubos/bitops.h>

.extern on_boot
.extern kmain
.extern cpu_die
.extern gdt_ptr
.extern gdt
.extern enable_paging

/*
 * page directory
 */
.extern __kpd
/*
 * first page table (maps 4 MiB)
 */
.extern __kpt

/*
code is loaded to LOAD_PHYS_ADDR,
We must enable paging, so that

   VIRTUAL	  ->	PHYSICAL
   0xc0000000     ->	0x00000000

Kernel is loaded on physical address PHYS_LOAD_ADDR by bootloader
	(see asm/memmap.h)
*/

.section .bootdata, "a"
.section .boottext, "ax"
.globl _start
_start:
	cli
	/* memset(page_directory, 0, 4096) */
	cld
	xorl %eax, %eax
	movl $0x1000, %ecx
	movl $__pa(__kpd), %edi
	rep stosl

	/* memset(page_table, 0, 4096) */
	movl $0x1000, %ecx
	movl $__pa(__kpt), %edi
	rep stosl

	/* setup page directory, that page_directory[0] and page_directory[768] points to page_table */
	movl $__pa(__kpt), %eax
	andw $0xf000, %ax
	movb $0b00100111, %al

	movl $__pa(__kpd), %edi
	/* page_directory[0] = page_table */
	movl %eax, __pa(__kpd)

	/* page_directory[768] = page_table */
	movl $768, %ecx
	movl %eax, (%edi,%ecx,4)

/* 
 * init page_table
 */
	xorl %eax, %eax
	movl $__pa(__kpt), %edi

ptbl_init_lpbeg:
	cmp $0x400, %eax
	jge ptbl_init_lpend

	movl %eax, %edx
	shl $12, %edx
	movb $0b00000011, %dl

/* 
 * clr bits 8-11 (avl bits)
 */
	andb $0xf0, %dh
	movl %edx, (%edi)
	incl %eax
	addl $0x4, %edi

	jmp ptbl_init_lpbeg
ptbl_init_lpend:

	movb $'a', 0xb8000
	movl $__pa(__kpd), %eax
	movl %eax, %cr3

	movl %cr0, %eax
	orl  $CR0_BIT_PG, %eax
	movl %eax, %cr0

/*
 * set gdt to KNOWN value
 */

	lgdt (gdt_ptr)
	movw $GDT_KDATA, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs
	movw %ax, %ss
	ljmpl $GDT_KCODE, $__flush
__flush:
	
	movl $__kstack_end, %esp
	jmp kmain
