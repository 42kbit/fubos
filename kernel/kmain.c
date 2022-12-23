/* on this line was a ton of cringe, so i removed it */

#include <asm/gdt.h>
#include <asm/x86.h>
#include <asm/page.h>

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

u32 ticks_passed = 0;

void timer_callback (struct isr_regs*){
	/*
	kprintf("Timer %u\n", ticks_passed++);
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

extern sym __conv_mem_start_addr;
extern sym __conv_mem_len;
extern sym __conv_mem_end_addr;

extern char multiboot2_header;

void kmain(void){
	arch_init();

	if (init_klog_buffer() < 0)
		cpu_die();
	kprintf("klog initialized successfully\n");
	kprintf("%%p = %p, %%u = %u, %%s = %s\n", (void*)0xdeadb, 15, "foo, bar!");
	kprintf("__conv_mem_start = %p\n__conv_mem_len = %p\n__conv_mem_end_start = %p\n",
			__symval(__conv_mem_start_addr, void*),
			__symval(__conv_mem_len,   	addr_t),
			__symval(__conv_mem_end_addr, void*)
			);
	kprintf("kmain: %p, multiboot_header: %p\n", (void*)kmain, (void*)&multiboot2_header);

	set_ebx(0);
	set_bh(1);
	kprintf("ebx: %u\n", get_ebx());

	kprintf("Paging test\n");
	struct pg_dir_node dir_node_sample = {
		.present 	= 0,
		.rd_wr 		= 1,
		.usr_spw 	= 1,
		.pwt 		= 0,
		.cache_off 	= 0,
		.acc		= 1,
		.avl0		= 0,
		.page_size	= 0,
		.avl		= 0,
		.adr		= 0
	};
	struct pg_tbl_node tbl_node_sample = {
		.present 	= 1,
		.rd_wr 		= 1,
		.usr_spw 	= 0,
		.pwt 		= 0,
		.cache_off 	= 0,
		.acc		= 0,
		.dirty		= 0,
		.pat		= 0,
		.global		= 0,
		.avl		= 0,
		.adr		= 0
	};

	/* maps lower 4 mib of memory to itself. */
	
	static struct pg_tbl kpg_tbl __aligned (PAGE_SIZE);
	static struct pg_dir kpg_dir __aligned (PAGE_SIZE);

	for (int i = 0; i < PG_TBL_NENT; i++){
		kpg_tbl.pt_nodes[i] = tbl_node_sample;
		kpg_tbl.pt_nodes[i].adr = i;
	}
	for (int i = 0; i < PG_DIR_NENT; i++){
		kpg_dir.pd_nodes[i] = dir_node_sample;
	}
	kpg_dir.pd_nodes[0].present = 1;
	kpg_dir.pd_nodes[0].adr = bitcut((addr_t)&kpg_tbl, 12, 20);

	set_page_dir (&kpg_dir);
	enable_paging ();

	kprintf ("cr3: %h\n", get_cr3());

	/* does page fault */
	* (char*)mib(4) = 5;

	init_timer(50);

	cpu_relax();
}
