#include <fubos/compiler_attributes.h>

#include <fubos/symbol.h>
#include <fubos/types.h>

#include <asm/x86.h>

#include "mb2.h"

#define __MLTB2_CHECKSUM\
	(MLTB2_MAGIC + MLTB2_ARCH_X86 + sizeof(struct mb2_header))

__section(".mb2") __aligned(16)
struct mb2_header mb2_header = {
	.magic 		= MLTB2_MAGIC,
	.architecture 	= MLTB2_ARCH_X86,
	.header_length	= sizeof(struct mb2_header),
	.checksum	= -__MLTB2_CHECKSUM,
	.end_tag	= {
		.type =  0,
		.flags = 0,
		.size =  8
	}
};
