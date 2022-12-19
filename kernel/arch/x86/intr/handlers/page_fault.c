#include <asm/isr.h>
#include <asm/x86.h>
#include <fubos/klog.h>

/* ../stub.c */
void stub_handler(struct isr_regs* isr_regs);

void on_page_fault(struct isr_regs* regs){
	u32 cr2 = get_cr2 ();
	kprintf("Page fault! Caused by %p\n", cr2);
	kprintf("  Reason: ");
	if (!(regs->errno & bit(0)))
		kprintf("Page not present.\n");
	cpu_die();
}
