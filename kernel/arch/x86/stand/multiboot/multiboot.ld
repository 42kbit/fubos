OUTPUT_FORMAT(elf32-i386)
ENTRY(_start)

SECTIONS
{
	. = 1M;
	.text BLOCK(4K) : ALIGN(4K) {
		*(.multiboot)
		*(.text)
	}
	.data BLOCK(4K) : ALIGN(4K) {*(.data)}
	.rodata BLOCK(4K) : ALIGN(4K) {*(.rodata)}
	.bss BLOCK(4K) : ALIGN(4K) {*(.bss)}

	. = ALIGN(4K);
	__kheap_begin = . ;
	. += 64K;
	__kheap_end = . ;
}
