#ifndef   __H_MEMMAP_H
#define   __H_MEMMAP_H

/* This header defines:
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

#define PHYS_LOAD_ADDR		PHYS_HIMEM
#define VIRT_LOAD_ADDR		0xc0000000 + PHYS_HIMEM

#ifndef __GNULD__
#	define BIOS_EDATA_LEN		kib(128)
#	define FREE_MEM_LEN		kib(512) - BIOS_IVT_LEN - BIOS_DATA_LEN
#	define BIOS_IVT_LEN 		kib(1)
#else  /* __GNULD__ */
#	define BIOS_EDATA_LEN		131072
#	define FREE_MEM_LEN		392192
#	define BIOS_IVT_LEN 		1024
#endif /* __GNULD__ */

#ifndef __ASSEMBLY__
#endif /* __ASSEMBLY__ */

#endif /* __H_MEMMAP_H */
