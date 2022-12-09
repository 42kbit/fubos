#include <fubos/compiler_attributes.h>
#include <fubos/boot_info.h>

#include <fubos/symbol.h>
#include <fubos/types.h>

#include <asm/x86.h>

#include "multiboot2.h"

#define __MLTB2_CHECKSUM\
	(MLTB2_MAGIC + MLTB2_ARCH_X86 + sizeof(struct multiboot2_header))

__section(".multiboot2") __aligned(16)
struct multiboot2_header multiboot2_header = {
	.magic 		= MLTB2_MAGIC,
	.architecture 	= MLTB2_ARCH_X86,
	.header_length	= sizeof(struct multiboot2_header),
	.checksum	= -__MLTB2_CHECKSUM,
	.end_tag	= {
		.type =  0,
		.flags = 0,
		.size =  8
	}
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
	kmain();
	cpu_die();
}
