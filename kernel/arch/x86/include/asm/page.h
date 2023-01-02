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

/* Next structs do define 2-level paging in x86 systems,
 * this includes:
 * 	struct pde <- Page Directory Entry
 * 	struct pte <- Page Table Entry
 */

struct pde {
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

struct pte {
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

struct pt {
	struct pte pt_nodes[PG_TBL_NENT];
};

struct pd {
	struct pde pd_nodes[PG_DIR_NENT];
};

#endif /* __ASSEMBLY__ */
#endif /* __GNULD__ */

#endif /* __H_PAGE_H */
