#include <asm/gdt.h>

/*
 * Using flat memory model
 */

#define GDT_32_ACCESS\
	(GDT_GRANULARITY | GDT_PROTMODE)

/* 
 * 0x9a
 */

#define KCODE_FLAGS\
	(GDT_READABLE | GDT_CODE | GDT_CORD | GDT_PRIV(0) | GDT_PRESENT)
/* 
 * 0x92 
 */

#define KDATA_FLAGS\
	(GDT_WRITEABLE | GDT_CORD | GDT_PRIV(0) | GDT_PRESENT)
/*
 * 0xfa
 */

#define UCODE_FLAGS\
	(GDT_READABLE | GDT_CODE | GDT_CORD | GDT_PRIV(3) | GDT_PRESENT)
/* 
 * 0xf2
 */

#define UDATA_FLAGS\
	(GDT_WRITEABLE | GDT_CORD | GDT_PRIV(3) | GDT_PRESENT)

struct gdt_node gdt[GDT_NENT] = {
	[GDT_IDX_NULL] = {0},
	[GDT_IDX_KCODE] = gdt_make_node(0, 0xfffff, KCODE_FLAGS, GDT_32_ACCESS),
	[GDT_IDX_KDATA] = gdt_make_node(0, 0xfffff, KDATA_FLAGS, GDT_32_ACCESS),
	[GDT_IDX_UCODE] = gdt_make_node(0, 0xfffff, UCODE_FLAGS, GDT_32_ACCESS),
	[GDT_IDX_UDATA] = gdt_make_node(0, 0xfffff, UDATA_FLAGS, GDT_32_ACCESS)
};

struct gdt_ptr gdt_ptr = {
	.size = GDT_NENT * sizeof(struct gdt_node) - 1,
	.ptr = (u32)&gdt
};
