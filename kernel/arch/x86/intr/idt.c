#include <asm/idt.h>
/* for selectors */
#include <asm/gdt.h>
#include <asm/x86.h>
#include <asm/pic.h>

#include <asm/isr.h>
#include <asm/page.h>

idt_entry_t 	idt[IDT_NENT];

idt_ptr_t	idt_ptr = {
	.size = IDT_NENT * sizeof(idt_entry_t) - 1,
	.ptr = (u32)&idt
};

intr_handler_t intr_handlers[IDT_NENT];

void idt_load_entry( idt_entry_t* table,
		u8 where,
		u32 handler,
		u16 selector,
		u8 gt,
		u8 dpl,
		u8 present)
{
	idt_entry_t e = idt_make_entry(handler, selector, gt, dpl, present);
	table[where] = e;
}

void stub_handler(struct isr_regs*);

void init_intr(void){
	for (int i = 0; i < IDT_NENT; i++){
		void* proc = isr_addr(i);
		idt_load_entry(idt, i, (u32)proc, GDT_KCODE, 
			IDT_GT_32_INTR, 0, 1);
		reg_handler(i, stub_handler);
	}
	reg_handler(14, on_page_fault);
	flush_idt(&idt_ptr);
}
