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
#include <fubos/string.h>

/* 
 * not arch independent code will be fixed later
 */

#include <asm/page.h>

void arch_init	(void);
void cpu_relax	(void) __noreturn;
void cpu_die	(void) __noreturn;

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

struct pde tm_pd[PG_TBL_NENT] __aligned(PAGE_SIZE);
struct pte tm_pt[PG_TBL_NENT] __aligned(PAGE_SIZE);

void kmain(struct boot_info* info){
	arch_init();

	if (init_klog_buffer() < 0)
		cpu_die();
	kprintf("klog initialized successfully\n");
	
	kprintf("Loader: %s\n", binfo_loader_name(info));

	struct boot_module* modules[BOOT_MAX_MODS];
	binfo_mods(info, modules);

	kprintf("Listing modules:\n");
	for (struct boot_module** module = modules;
			*module != NULL;
			module++)
	{
		kprintf (" Name: %s\n Addr: %p\n", bmod_name(*module), bmod_addr(*module));
	}

	/*
	struct pde* kpd = __symval(__kpd, struct pde*);
	print_pde (kpd + 768);
	*/

	/* TODO: test module, setup virtual memory for it, then jump to elf entry. */

	struct elf_header32 {
		char e_ident[16];
		short e_type,
		      e_machine;
		int   e_version;
		int   e_entry;
	};
	/* physical address of elf header */
	struct elf_header32* mod_addr = (struct elf_header32*)bmod_addr(modules[0]);

	/* clone kernel page table and directory */
	extern sym __kpd;
	memcpy (tm_pd, __symval(__kpd, void*), sizeof(struct pde) * PG_DIR_NENT);
	extern sym __kpt;
	memcpy (tm_pt, __symval(__kpt, void*), sizeof(struct pte) * PG_TBL_NENT);
	/* module is linked to virtual address 0x08048000, configure pagetable for it. */
	tm_pd[0x08048000 / mib(4)].pde = PDE_P | PDE_RDWR | PDE_US | PDE_ACC | PDE_ADDR((addr_t)virt_to_phys(tm_pt));
	print_pde(tm_pd + (0x08048000 / mib(4)));

	for (int i = 0; i < PG_TBL_NENT; i++){
		tm_pt[i].pte = PTE_P | PTE_RDWR | PTE_US | PTE_ADDR((addr_t)mod_addr);
	}

	init_timer(50);
	/* swap page table, and jump to "process" */
	set_cr3((addr_t)virt_to_phys(tm_pd));
	kprintf("%p\n", tm_pt);
	kprintf("%s\n", 0x08048000);
	kprintf ("Im still standing\n");
	asm volatile ("jmp 0x08048054\n\t");

	cpu_relax();
}
