#ifndef __H_PAGE_H
#define __H_PAGE_H

#include <asm/isr.h>

#define PAGE_SIZE 4096
#define PG_TBL_NENT 1024
#define PG_DIR_NENT 1024

#ifndef __ASSEMBLY__

#include <fubos/compiler_attributes.h>

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
typedef struct pg_dir_node pg_dir_node_t;

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
typedef struct pg_tbl_node pg_tbl_node_t;

struct pg_tbl {
	pg_tbl_node_t pt_nodes[PG_TBL_NENT];
};
typedef struct pg_tbl pg_tbl_t;

struct pg_dir {
	pg_dir_node_t pd_nodes[PG_DIR_NENT];
};
typedef struct pg_dir pg_dir_t;

void on_page_fault(isr_regs_t*);

#endif /* __ASSEMBLY__ */
#endif /* __H_PAGE_H */
