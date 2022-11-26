/* seg_reload.S */
#include <asm/gdt.h>
#include <asm/idt.h>
#include <asm/isr.h>

static inline void enable_intr(void){
	asm volatile ("sti;");
}

void cpu_relax(void);

/* idt.c */
void init_intr(void);
/* pic.c */
void init_irq(void);

void arch_init(void){
	flush_gdt(&gdt_ptr);

	init_intr();
	init_irq();
	enable_intr();
}

void cpu_relax(void) {
	while (1) 
		asm volatile("hlt");
}
