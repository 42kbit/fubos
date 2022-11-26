#include <asm/idt.h>
#include <asm/isr.h>

/* VGA bullshit will be removed later */

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

void stub_handler(isr_regs_t* regs);

void on_page_fault(isr_regs_t* regs){
	stub_handler(regs);
}

/* Unhandled exceptions go here */
void stub_handler(isr_regs_t* regs){
	char buf[8];
	sget_hex(&(regs->intno), 4, buf);
	vga_write(buf, 8);
}
