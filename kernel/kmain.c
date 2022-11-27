/* on this line was a ton of cringe, so i removed it */

#include <asm/gdt.h>
#include <asm/x86.h>

#include <fubos/ints.h>
#include <fubos/bitops.h>
#include <fubos/symbol.h>

#include <fubos/klog.h>

/* not arch independent code will be fixed later */
void arch_init	(void);
void cpu_relax	(void);
void cpu_die	(void);

#define __X86_INT(x) asm volatile ( "int $" #x ";" )

#include <asm/isr.h>

void timer_callback (isr_regs_t*){
	kprintf("Timer\n");
}

void init_timer (u32 freq){
	reg_handler(IRQ(0), timer_callback);
	u32 divisor = 1193180 / freq;
	outb(0x43, 0x36);

	u8 l=(u8)(divisor&0xFF);
	u8 h=(u8)((divisor>>8)&0xFF);

	outb(0x40, l);
	outb(0x40, h);
}

void kmain(void){
	arch_init();

	if (init_klog_buffer() < 0)
		cpu_die();
	kprintf("klog initialized successfully\n");

	init_timer(50);

	cpu_relax();
}
