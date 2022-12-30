#ifndef __H_PAGE_H
#define __H_PAGE_H

#define PG_TBL_NENT 1024
#define PG_DIR_NENT 1024

#define PAGE_SIZE  4096
#define PAGE_SHIFT 12

#ifndef __GNULD__

#include <asm/isr.h>

#ifndef __ASSEMBLY__

#include <fubos/compiler_attributes.h>
#include <asm/memmap.h>

struct pg_dir_node {
	u32
	   present 	: 1,
	   rd_wr	: 1,
	   usr_spw	: 1,
	   pwt		: 1,
	   cache_off	: 1,
	   acc		: 1,
	   avl0		: 1,
	   page_size	: 1,
	   avl		: 4,
	   adr		: 20;
} __packed;

struct pg_tbl_node {
	u32
	   present 	: 1,
	   rd_wr	: 1,
	   usr_spw	: 1,
	   pwt		: 1,
	   cache_off	: 1,
	   acc		: 1,
	   dirty	: 1,
	   pat		: 1,
	   global	: 1,
	   avl		: 3,
	   adr		: 20;
} __packed;

struct pg_tbl {
	struct pg_tbl_node pt_nodes[PG_TBL_NENT];
};

struct pg_dir {
	struct pg_dir_node pd_nodes[PG_DIR_NENT];
};

static inline void* virt_to_phys(volatile void * addr){
	return __pa(addr);
}

/* sets PG bit on PSW */
void enable_paging (void);

/* sets cr3 */
void set_page_dir (struct pg_dir* new_dir);

/* kernel/intr/handlers/page_fault.c */
void on_page_fault (struct isr_regs*);

#endif /* __ASSEMBLY__ */
#endif /* __GNULD__ */

#endif /* __H_PAGE_H */
