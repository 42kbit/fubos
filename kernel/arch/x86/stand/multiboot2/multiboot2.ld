#undef i386
OUTPUT_FORMAT(elf32-i386)
ENTRY(_start)

#include <asm/memmap.h>
#include <asm/page.h>

__phys_load_addr = PHYS_LOAD_ADDR;
__phys_load_len  = 0xffffffff - PHYS_LOAD_ADDR + 1;

SECTIONS
{
	/* entry.S */
	. = VIRT_LOAD_ADDR;

	.text : AT(PHYS_LOAD_ADDR) {
		__text_begin = . ;
		*(.text)
		__text_end = . ;
	}

	__data_begin = . ;
	.data BLOCK(4K) : ALIGN(4K) {*(.data)}
	__data_end = . ;

	__rodata_begin = . ;
	.rodata BLOCK(4K) : ALIGN(4K) {*(.rodata)}
	__rodata_end = . ;

	__bss_begin = . ;
	.bss BLOCK(4K) : ALIGN(4K) {*(.bss)}
	__bss_end = . ;

	. = ALIGN(4K);
	__kheap_begin = . ;
	. += 64K;
	__kheap_end = . ;
	/* entry.S */
	. = ALIGN(4K);
	__kpd = . ;
	. = ALIGN(4K);
	__kpt = . ;
	. = ALIGN(4K);
	. += 64K;
	__kstack = . ;
}
