#include <asm/gdt.h>
gdt_entry_t gdt[GDT_NENT] = {
	{0},
	gdt_make_entry(0, 0xfffff, 0x9a, 0xc),
	gdt_make_entry(0, 0xfffff, 0x92, 0xc),
	gdt_make_entry(0, 0xfffff, 0xfa, 0xc),
	gdt_make_entry(0, 0xfffff, 0xf2, 0xc)
};

gdt_ptr_t gdt_ptr = {
	.size = GDT_NENT * sizeof(gdt_entry_t) - 1,
	.ptr = (u32)&gdt
};
