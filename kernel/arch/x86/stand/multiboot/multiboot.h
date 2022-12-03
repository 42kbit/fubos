#ifndef _H_MULTIBOOT_H
#define _H_MULTIBOOT_H

#include <fubos/bitops.h>

#define MLTB1_MAGIC 	0x1BADB002
#define MLTB1_PAGING  	bit(0)
#define MLTB1_MEMINFO 	bit(1)
#define MLTB1_VIDEOINFO	bit(2)
#define MLTB1_LOADINFO  bit(16)

#ifndef __ASSEMBLY__

/*
https://www.gnu.org/software/grub/manual/multiboot/multiboot.html#Header-magic-fields

3.1.1 The layout of Multiboot header

The layout of the Multiboot header must be as follows:
Offset	Type	Field Name	Note
0	u32	magic		required
4	u32	flags		required
8	u32	checksum	required
12	u32	header_addr	if flags[16] is set
16	u32	load_addr	if flags[16] is set
20	u32	load_end_addr	if flags[16] is set
24	u32	bss_end_addr	if flags[16] is set
28	u32	entry_addr	if flags[16] is set
32	u32	mode_type	if flags[2] is set
36	u32	width		if flags[2] is set
40	u32	height		if flags[2] is set
44	u32	depth		if flags[2] is set
*/

#include <fubos/ints.h>

struct multiboot_header {
	u32 magic,
	    flags,
	    checksum,
	    header_addr,
	    load_addr,
	    load_end_addr,
	    bss_end_addr,
	    entry_addr,
	    mode_type,
	    width,
	    height,
	    depth;
};

#endif /* __ASSEMBLY__ */

#endif /* _H_MULTIBOOT_H */
