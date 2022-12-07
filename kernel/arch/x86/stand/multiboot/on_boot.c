#include <fubos/compiler_attributes.h>
#include <fubos/boot_info.h>

#include <fubos/symbol.h>
#include <fubos/types.h>

#include <asm/x86.h>

#include "multiboot.h"

#define __MLTB1_FLAGS (MLTB1_PAGING | MLTB1_MEMINFO)

__section(".multiboot") __aligned(16)
struct multiboot_header multiboot_header = {
	.magic = 	MLTB1_MAGIC,
	.flags = 	__MLTB1_FLAGS,
	.checksum = 	-(__MLTB1_FLAGS + MLTB1_MAGIC),
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
	/* ebx stores address of multiboot_info structure */
	struct multiboot_info* mboot_info =
		(struct multiboot_info*) get_ebx();
	kmain();
	cpu_die();
}
