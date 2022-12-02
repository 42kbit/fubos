#include <fubos/klog.h>
#include <asm/idt.h>
#include <asm/isr.h>
void stub_handler(isr_regs_t* regs);

/* Unhandled exceptions go here */
void stub_handler(isr_regs_t* regs){
	kprintf("Unhandled exception %u\n", regs->intno);
}
