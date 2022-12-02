#include <asm/gdt.h>
#include <asm/idt.h>
#include <asm/isr.h>

static inline void enable_intr(void){
	asm volatile ("sti;");
}

void cpu_relax(void);

/* intr/idt.c */
void init_intr(void);
/* intr/pic.c */
void init_irq(void);

void arch_init(void){
	flush_gdt(&gdt_ptr);

#ifdef CONFIG_LOG_INPLACE
void __init_vga(void);
	__init_vga();
#endif

	init_intr();
	init_irq();
	enable_intr();
}

void cpu_relax(void) {
	while (1) 
		asm volatile("hlt");
}

void cpu_die(void){
	while (1){
		asm volatile ("cli; hlt;");
	}
}
