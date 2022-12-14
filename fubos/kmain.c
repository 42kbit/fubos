/* 
 * on this line was a ton of cringe, so i removed it
 */

#include <asm/gdt.h>
#include <asm/x86.h>
#include <asm/page.h>

#include <fubos/ints.h>
#include <fubos/bitops.h>
#include <fubos/symbol.h>

#include <fubos/klog.h>
#include <fubos/boot.h>

/* 
 * not arch independent code will be fixed later
 */

void arch_init	(void);
void cpu_relax	(void) __noreturn;
void cpu_die	(void) __noreturn;

#define __X86_INT(x) asm volatile ( "int $" #x ";" )

#include <asm/isr.h>

u32 ticks_passed = 0;

void timer_callback (struct isr_regs*){
/*
 * kprintf("Timer %u\n", ticks_passed++);
 */
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

extern sym __phys_load_addr;
extern sym __phys_load_len;

extern sym __kpd;
extern sym __kpt;

void print_pde (struct pde * ent){
	kprintf(" Present: %u\n"
		" Read/Write: %u\n"
		" Public: %u\n"
		" Write-Through: %u\n"
		" Cache Disabled: %u\n"
		" Accessed: %u\n"
		" 4 MiB Page: %u\n"
		" Address: %p\n",
		pde_present(ent), pde_rdwr(ent),
		pde_public(ent), pde_write_through(ent),
		pde_cache_disabled(ent), pde_accessed(ent),
		pde_4mib_page(ent), pde_addr(ent));
}

void kmain(struct boot_info* info){
	arch_init();

	if (init_klog_buffer() < 0)
		cpu_die();

	kprintf("klog initialized successfully\n");
	kprintf("Loader: %s\n", binfo_loader_name(info));
	kprintf("virtual kmain: %p\nphys kmain:%p\n", (void*)kmain, virt_to_phys(kmain));

	struct pde* kpd = __symval(__kpd, struct pde*);
	print_pde (kpd + 768);

	init_timer(50);

	cpu_relax();
}
