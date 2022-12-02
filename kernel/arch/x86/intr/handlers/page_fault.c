#include <asm/isr.h>

/* ../stub.c */
void stub_handler(struct isr_regs* isr_regs);

void on_page_fault(struct isr_regs* regs){
	stub_handler(regs);
}
