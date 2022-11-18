/* seg_reload.S */
#include <asm/gdt.h>
#include <asm/idt.h>
#include "isr.h"

void cpu_relax(void);

void arch_spec(void){
	flush_gdt(&gdt_ptr);

	for (int i = 0; i < IDT_NENT; i++){
		void* proc = isr_addr(i);
		idt_load_entry(idt, i, (u32)proc, GDT_KCODE, 
			IDT_GT_32_INTR, 0);
	}
	flush_idt(&idt_ptr);
}

void cpu_relax(void) {
	while (1) 
		asm volatile("hlt");
}
