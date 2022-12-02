#include <fubos/klog.h>
#include <fubos/bitops.h>
#include <asm/vga.h>

struct vga_node * const vga_text = (vga_node_t*) 0xb8000;
off_t vga_text_off = 0;

#define VGA_LAST_LINE_OFF VGA_BUFFER_LEN - VGA_WIDTH

static inline void vga_scroll(){
	vga_text_off %= VGA_BUFFER_LEN;
	for (int i = 0; i < VGA_BUFFER_LEN; i++){
		vga_text[i].c = vga_text[i + VGA_WIDTH].c;
	}
	for (int i = VGA_LAST_LINE_OFF; i < VGA_BUFFER_LEN; i++){
		vga_text[i].c = ' ';
	}
	/* set offset to last line */
	vga_text_off = VGA_LAST_LINE_OFF;
}

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
	if (vga_text_off >= VGA_BUFFER_LEN){
		vga_scroll();
	}
}

void __init_vga(){
	for (int i = 0; i < VGA_BUFFER_LEN; i++){
		vga_text[i].c = ' ';
	}
}

void __klog_buffer_flush(){
	char c = klog_getc_at(klog_buffer_off - 1);
	vga_putc(c);
}
