#define __ASSEMBLY__
#include <asm/gdt.h>
/* 
 * asm/idt.h
 * void flush_idt(idt_ptr_t*);
*/
.globl flush_idt
flush_idt:
	movl 4(%esp), %eax
	lidt (%eax)
	ret
