#ifndef _H_MULTIBOOT_H
#define _H_MULTIBOOT_H

#include <fubos/bitops.h>

#define MLTB2_ALIGN	16
#define MLTB2_MAGIC 	0xE85250D6
#define MLTB2_ARCH_X86	0

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


/* Multiboot header tags
 */

struct mb2_generic_tag {
	u16 type,
	    flags;
	u32 size;
};

struct mb2_header {
	u32 magic,
	    architecture,
	    header_length,
	    checksum;
	struct mb2_generic_tag end_tag;
};

/* Multiboot boot info tags
 */
struct mb2_binfo_header {
	u32 total_size,
	    reserved;
};

/* Metadata for info structure
 * Located in memory first
 */
struct mb2_binfo_meta {
	u32 type,
	    size;
};

struct mb2_binfo_meminfo {
	struct mb2_binfo_meta meta;
	u32 mem_lower,
	    mem_upper;
};

struct mb2_binfo_bios_dev {
	struct mb2_binfo_meta meta;
	u32 biosdev,
	    partition,
	    sub_partition;
};

struct mb2_binfo_cmd {
	struct mb2_binfo_meta meta;
	u8 string[];
};

struct mb2_binfo_module {
	struct mb2_binfo_meta meta;
	u32 mod_start,
	    mod_end;
	u8  string[];
};

#endif /* __ASSEMBLY__ */

#endif /* _H_MULTIBOOT_H */
