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

struct boot_info {
	const char * loader_name;
};

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

#define MB2_BINFO_MEMINFO 4
struct mb2_binfo_meminfo {
	struct mb2_binfo_meta meta;
	u32 mem_lower,
	    mem_upper;
};

#define MB2_BINFO_BIOSDEV 5
struct mb2_binfo_biosdev {
	struct mb2_binfo_meta meta;
	u32 biosdev,
	    partition,
	    sub_partition;
};

#define MB2_BINFO_CMD 1
struct mb2_binfo_cmd {
	struct mb2_binfo_meta meta;
	char string[];
};

#define MB2_BINFO_MODULE 3
struct mb2_binfo_module {
	struct mb2_binfo_meta meta;
	u32 mod_start,
	    mod_end;
	char string[];
};

#define MB2_BINFO_ELFSYMS 9
struct mb2_binfo_elfsyms {
	struct mb2_binfo_meta meta;
};

#define MB2_BINFO_MEMMAP 6
struct mb2_binfo_memmap {
	struct mb2_binfo_meta meta;
};

#define MB2_BINFO_LOADERNAME 2
struct mb2_binfo_loadername {
	struct mb2_binfo_meta meta;
	char string[];
};

#define MB2_BINFO_APM 10
struct mb2_binfo_apm {
	struct mb2_binfo_meta meta;
};

#define MB2_BINFO_VBE 7
struct mb2_binfo_vbe {
	struct mb2_binfo_meta meta;
};

#endif /* __ASSEMBLY__ */

#endif /* _H_MULTIBOOT_H */
