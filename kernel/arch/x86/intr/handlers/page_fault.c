#include <asm/isr.h>

/* ../stub.c */
void stub_handler(struct isr_regs* isr_regs);

void on_page_fault(isr_regs_t* regs){
	stub_handler(regs);
}
