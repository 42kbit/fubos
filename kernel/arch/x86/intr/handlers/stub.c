#include <fubos/klog.h>
#include <asm/idt.h>
#include <asm/isr.h>

/* Unhandled exceptions go here */
void stub_handler(struct isr_regs* regs){
	kprintf("Unhandled exception %u\n", regs->intno);
}
