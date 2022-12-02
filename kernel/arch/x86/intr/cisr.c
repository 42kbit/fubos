#include <asm/isr.h>
#include <asm/pic.h>

intr_handler_t intr_handlers[IDT_NENT];

void stub_handler (struct isr_regs*);

void reg_handler(u8 intno, intr_handler_t handler){
	intr_handlers[intno] = handler;
}

/* i could do that bullshit in asm but meh...*/
void isr_handler (struct isr_regs sframe){
	if (isr_is_irq(sframe.intno)){
		pic_send_eoi(isr_to_irq(sframe.intno));
	}
	intr_handler_t handler = intr_handlers[sframe.intno];
	if (handler){
		handler(&sframe);
	}
}
