#undef i386
OUTPUT_FORMAT(elf32-i386)
ENTRY(_start)

#include <asm/memmap.h>
#include <asm/page.h>

__phys_load_addr = PHYS_LOAD_ADDR;
__phys_load_len  = 0xffffffff - PHYS_LOAD_ADDR + 1;

SECTIONS
{
	. = PHYS_LOAD_ADDR;
	/* entry.S */
	.boottext : AT(ADDR(.boottext)){
		*(.boottext)
	}

	.bootdata : AT(ADDR(.bootdata)){
		*(.bootdata)
	}

	. += PAGE_OFFSET;
	__text_begin = . ;
	.text ALIGN(PAGE_SIZE) : AT(ADDR(.text) - PAGE_OFFSET) {
		*(.text)
	}
	__text_end = . ;

	__data_begin = . ;
	.data ALIGN(PAGE_SIZE) : AT(ADDR(.data) - PAGE_OFFSET) {
		*(.data)
	}
	__data_end = . ;

	__rodata_begin = . ;
	.rodata ALIGN(PAGE_SIZE) : AT(ADDR(.rodata) - PAGE_OFFSET) {
		*(.rodata)
	}
	__rodata_end = . ;

	__bss_begin = . ;
	.bss ALIGN(PAGE_SIZE) : AT(ADDR(.bss) - PAGE_OFFSET) {
		*(.bss)
		. = ALIGN(PAGE_SIZE);
		__kheap_begin = ABSOLUTE(.);
		. += 64K;
		__kheap_end = ABSOLUTE(.);
		/* entry.S */
		. = ALIGN(PAGE_SIZE);
		__kpd = ABSOLUTE(.);
		. += PAGE_SIZE;
		__kpt = ABSOLUTE(.);
		. += PAGE_SIZE;
		__kstack_begin = ABSOLUTE(.);
		. += 64K;
		__kstack_end = ABSOLUTE(.);
		. += PAGE_SIZE;
		__mb2_binfo_copy = ABSOLUTE(.);
		. += PAGE_SIZE;
	}
	__bss_end = . ;
}
