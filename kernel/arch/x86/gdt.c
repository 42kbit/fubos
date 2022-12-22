#include <asm/gdt.h>
struct gdt_node gdt[GDT_NENT] = {
	{0},
	gdt_make_node(0, 0xfffff, 0x9a, 0xc),
	gdt_make_node(0, 0xfffff, 0x92, 0xc),
	gdt_make_node(0, 0xfffff, 0xfa, 0xc),
	gdt_make_node(0, 0xfffff, 0xf2, 0xc)
};

struct gdt_ptr gdt_ptr = {
	.size = GDT_NENT * sizeof(struct gdt_node) - 1,
	.ptr = (u32)&gdt
};
