OUTPUT_FORMAT(elf32-i386)
ENTRY(_start)

/* Memory map defined here.
	asm/memmap.h

__conv* variables defined in entry.S

__conv_mem_start_addr = FREE_MEM_ADDR
__conv_mem_len = FREE_MEM_LEN
__conv_mem_end_addr = (__conv_mem_start_addr + __conv_mem_len)

*/

SECTIONS
{
	. = __conv_mem_start_addr;

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

	. = __conv_mem_end_addr - 64;
	__multiboot_begin = . ;
	.multiboot : AT(0x0){ *(.multiboot) }
	__multiboot_end = . ;

	. = 1M;
	. = ALIGN(4K);
	__kheap_begin = . ;
	. += 64K;
	__kheap_end = . ;
}
