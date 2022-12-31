#ifndef   __H_MEMMAP_H
#define   __H_MEMMAP_H

/* 
 * This header defines:
 * memory layout in x86 systems
 * fubos virtual memory layout
 */

#include <fubos/bitops.h>

#define BIOS_IVT_ADDR		0x00000000
#define BIOS_DATA_ADDR 	 	0x00000400
#define BIOS_DATA_LEN	 	256
#define FREE_MEM_ADDR		0x00000500
#define BIOS_EDATA_ADDR		0x00080000

/* 1 Mib */
#define PHYS_HIMEM		0x00100000

/* mapped kernel start addr */
#define VIRT_HIMEM		0xc0000000

#define PHYS_LOAD_ADDR		PHYS_HIMEM
#define VIRT_LOAD_ADDR		VIRT_HIMEM + PHYS_HIMEM

#define PAGE_OFFSET 		VIRT_LOAD_ADDR - PHYS_LOAD_ADDR

/*
	Same as following, but could be used in GNU linker script.

	#define BIOS_EDATA_LEN		kib(128)
	#define FREE_MEM_LEN		kib(512) - BIOS_IVT_LEN - BIOS_DATA_LEN
	#define BIOS_IVT_LEN 		kib(1)
*/

#define BIOS_EDATA_LEN		131072
#define FREE_MEM_LEN		392192
#define BIOS_IVT_LEN 		1024

#ifndef __GNULD__

#define __pa(x) (x - PAGE_OFFSET)

#ifndef __ASSEMBLY__

#	include <fubos/types.h>
#	undef __pa
#	define __pa(x) ((void*)((char*)(x) - PAGE_OFFSET))

#endif /* __ASSEMBLY__ */
#endif /* __GNULD__ */

#endif /* __H_MEMMAP_H */
