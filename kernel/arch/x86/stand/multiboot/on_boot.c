#include <fubos/compiler_attributes.h>
#include <fubos/boot_info.h>

#include <fubos/symbol.h>
#include <fubos/types.h>

#include "multiboot.h"

extern sym __conv_mem_start_addr;
extern sym __conv_mem_len;
extern sym __conv_mem_end_addr;

extern sym __multiboot_begin;
extern sym __multiboot_end;

extern sym __text_begin;
extern sym __text_end;

extern sym __data_begin;
extern sym __data_end;

extern sym __rodata_begin;
extern sym __rodata_end;

extern sym __bss_begin;
extern sym __bss_end;

extern sym __kheap_end;

extern sym _start;

#define __MLTB1_FLAGS (MLTB1_PAGING | MLTB1_MEMINFO)

__section(".multiboot")
struct multiboot_header multiboot_header = {
	.magic = 	MLTB1_MAGIC,
	.flags = 	__MLTB1_FLAGS,
	.checksum = 	-(__MLTB1_FLAGS + MLTB1_MAGIC),
	/*
	.header_addr = 	(addr_t)&multiboot_header,
	.load_addr = 	__symval(__text_begin, addr_t),
	.load_end_addr =__symval(__rodata_end, addr_t),
	.bss_end_addr = __symval(__bss_end, addr_t),
	.entry_addr = 	__symval(_start, addr_t)
	*/
};

/* definition in include/fubos/boot_info.h */
struct boot_info boot_info;

/* kernel/kmain.c */
void kmain	(void);

/* kernel/kmain.c */
__noreturn
void cpu_die	(void);

__noreturn
void on_boot(void){
	kmain();
	cpu_die();
}
