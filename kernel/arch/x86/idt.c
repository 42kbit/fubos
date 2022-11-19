#include <asm/idt.h>
/* for selectors */
#include <asm/gdt.h>
#include <asm/x86.h>
#include <asm/pic.h>

#include <asm/isr.h>

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

void reg_handler(u8 intno, intr_handler_t handler){
	intr_handlers[intno] = handler;
}

/* to organize code, all handlers in intr_handlers.c */
void stub_handler (isr_regs_t*);

void init_intr(void){
	for (int i = 0; i < IDT_NENT; i++){
		void* proc = isr_addr(i);
		idt_load_entry(idt, i, (u32)proc, GDT_KCODE, 
			IDT_GT_32_INTR, 0, 1);
		reg_handler(i, stub_handler);
	}
	flush_idt(&idt_ptr);
}

/* i could do that bullshit in asm but meh...*/
void isr_handler (isr_regs_t sframe){
	if (isr_is_irq(sframe.intno)){
		pic_send_eoi(isr_to_irq(sframe.intno));
	}
	intr_handler_t handler = intr_handlers[sframe.intno];
	if (handler){
		handler(&sframe);
	}
}
