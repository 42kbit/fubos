#ifndef __H_PAGE_H
#define __H_PAGE_H

#define PG_TBL_NENT 1024
#define PG_DIR_NENT 1024

#define PAGE_SIZE  4096
#define PAGE_SHIFT 12

#ifndef __GNULD__

#include <asm/isr.h>

#define PDE_P 		(bit(0))
#define PDE_RDWR	(bit(1))
#define PDE_US 		(bit(2))
#define PDE_PWT 	(bit(3))
#define PDE_CD 		(bit(4))
#define PDE_ACC 	(bit(5))
#define PDE_AVL0	(bit(6))
#define PDE_PS 		(bit(7))
#define PDE_AVL(x)	(bitoff(x, 8))
#define PDE_ADDR(x)	(bitcut(x, 12, 20) << 12)

#define PTE_P 		(bit(0))
#define PTE_RDWR	(bit(1))
#define PTE_US 		(bit(2))
#define PTE_PWT 	(bit(3))
#define PTE_PCD 	(bit(4))
#define PTE_ACC 	(bit(5))
#define PTE_D		(bit(6))
#define PTE_PAT 	(bit(7))
#define PTE_G	 	(bit(8))
#define PTE_AVL(x)	(bitoff(x, 9))
#define PTE_ADDR(x)	(bitcut(x, 12, 20) << 12)

#ifndef __ASSEMBLY__

#include <fubos/compiler_attributes.h>
#include <asm/memmap.h>

/* Next structs do define 2-level paging in x86 systems,
 * this includes:
 * 	struct pde <- Page Directory Entry
 * 	struct pte <- Page Table Entry
 */

struct pde {
	u32 pde;
} __packed;

struct pte {
	u32 pte;
} __packed;

#define pde_present(x) 		!!((x)->pde & PDE_P)
#define pde_rdwr(x) 		!!((x)->pde & PDE_RDWR)
#define pde_public(x) 		!!((x)->pde & PDE_US)
#define pde_write_through(x) 	!!((x)->pde & PDE_PWT)
#define pde_cache_disabled(x) 	!!((x)->pde & PDE_CD)
#define pde_accessed(x) 	!!((x)->pde & PDE_ACC)
#define pde_4mib_page(x) 	!!((x)->pde & PDE_PS)
#define pde_addr(x) 		(bitcut((x)->pde, 12, 20))

#define pte_present(x) 		!!((x)->pte & PTE_P)
#define pte_rdwr(x) 		!!((x)->pte & PTE_RDWR)
#define pte_public(x) 		!!((x)->pte & PTE_US)
#define pte_write_through(x) 	!!((x)->pte & PTE_PWT)
#define pte_cache_disabled(x) 	!!((x)->pte & PTE_CD)
#define pte_accessed(x) 	!!((x)->pte & PTE_ACC)
#define pte_dirty(x) 		!!((x)->pte & PTE_D)
#define pte_pat(x) 		!!((x)->pte & PTE_PAT)
#define pte_global(x) 		!!((x)->pte & PTE_GLOBAL)
#define pte_addr(x) 		(bitcut((x)->pte, 12, 20))

#endif /* __ASSEMBLY__ */
#endif /* __GNULD__ */

#endif /* __H_PAGE_H */
