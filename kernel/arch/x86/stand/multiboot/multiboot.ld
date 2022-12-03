OUTPUT_FORMAT(elf32-i386)
ENTRY(_start)

__kernel_load_addr = 1M;

SECTIONS
{
	. = __kernel_load_addr;

	.multiboot : {
		__multiboot_begin = . ;
		*(.multiboot)
		__multiboot_end = . ;
	}

	.text BLOCK(4K) : ALIGN(4K) {
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
}
