#include <fubos/compiler_attributes.h>
#include <fubos/boot_info.h>
#include "multiboot.h"

#define __MLTB1_FLAGS (MLTB1_PAGING | MLTB1_MEMINFO)

__section(".multiboot")
struct multiboot_header multiboot_header = {
	.magic = MLTB1_MAGIC,
	.flags = __MLTB1_FLAGS,
	.checksum = -(__MLTB1_FLAGS + MLTB1_MAGIC)
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