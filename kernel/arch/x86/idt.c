#include <asm/idt.h>
/* for selectors */
#include <asm/gdt.h>

#include "isr.h"

idt_entry_t 	idt[IDT_NENT];

idt_ptr_t	idt_ptr = {
	.size = IDT_NENT * sizeof(idt_entry_t) - 1,
	.ptr = (u32)&idt
};

void idt_load_entry( idt_entry_t* table,
		u8 where,
		u32 handler,
		u16 selector,
		u8 gt,
		u8 dpl )
{
	idt_entry_t e = idt_make_entry(handler, selector, gt, dpl);
	table[where] = e;
}

/* not arch independent code will be fixed later */

static volatile u8 * const vga_text = (volatile u8*) 0xb8000;
#define get_hex_digit(x)\
	(x <= 9? (x+'0') : (x-10+'a'))
static inline void sget_hex(const void* _mem, u32 len, char* buf){
	const char* mem = _mem;
	for (i32 i = 0; i < len; i++){
		/* works for little endian */
		buf[i * 2 + 1] = get_hex_digit(bitcut(mem[i], 0, 4));
		buf[i * 2 + 0] = get_hex_digit(bitcut(mem[i], 4, 4));
	}
}

static inline void vga_write(const char* str, u32 len){
	for (i32 i = 0; i < len; i++){
		vga_text[i*2] = str[i];
	}
}

void isr_handler (isr_regs_t sframe){
	char val[8];
	sget_hex(&(sframe.intno), 4, val);
	vga_write(val, 8);
}
