#include <fubos/klog.h>
#include <fubos/bitops.h>
#include <asm/vga.h>

vga_node_t * const vga_text = (vga_node_t*) 0xb8000;
off_t vga_text_off = 0;

#error "TODO VGA DRIVER"

static inline void vga_putc(char c){
	switch (c){
	case '\n':
		vga_text_off -= vga_text_off % VGA_WIDTH;
		vga_text_off += VGA_WIDTH;
		break;
	default:
		vga_text[vga_text_off].c = c;
		vga_text_off += 1;
		break;
	}
	vga_text_off %= VGA_BUFFER_LEN;
}

void __klog_buffer_flush(){
	char c = klog_getc_at(klog_buffer_off - 1);
	vga_putc(c);
}
