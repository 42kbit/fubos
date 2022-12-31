#define __ASSEMBLY__
#include <asm/gdt.h>

/* 
 * asm/gdt.h
 * void flush_gdt(gdt_ptr_t*);
*/

.globl flush_gdt
flush_gdt:
	mov 4(%esp), %eax
	lgdt (%eax)
	
	movw $GDT_KDATA, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs
	movw %ax, %ss
	ljmpl $GDT_KCODE, $__flush
__flush:
	ret

/* 
 * asm/idt.h
 * void flush_idt(idt_ptr_t*);
*/
.globl flush_idt
flush_idt:
	movl 4(%esp), %eax
	lidt (%eax)
	ret
