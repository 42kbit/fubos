#ifndef   __H_MEMMAP_H
#define   __H_MEMMAP_H

#include <fubos/bitops.h>

#define BIOS_IVT_ADDR		(0x00000000)
#define	BIOS_IVT_LEN 		kib(1)

#define BIOS_DATA_ADDR 	 	(0x00000400)
#define BIOS_DATA_LEN	 	256

#define FREE_MEM_ADDR		(0x00000500)
#define FREE_MEM_LEN		kib(512) - BIOS_IVT_LEN - BIOS_DATA_LEN

#define BIOS_EDATA_ADDR		(0x00080000)
#define BIOS_EDATA_LEN		kib(128)

#ifndef __ASSEMBLY__
#endif /* __ASSEMBLY__ */

#endif /* __H_MEMMAP_H */
