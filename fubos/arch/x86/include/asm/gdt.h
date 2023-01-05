#ifndef __H_GDT_H
#define __H_GDT_H

#include <fubos/bitops.h>
#include <fubos/assert.h>

/*
 * dummy, kernel code/data, user code/data
 * */
#define GDT_NENT 5

#define GDT_SZENT 8
#define GDT_IDX_NULL 0

#define GDT_IDX_NULL  0
#define GDT_IDX_KCODE 1
#define GDT_IDX_KDATA 2
#define GDT_IDX_UCODE 3
#define GDT_IDX_UDATA 4

#define GDT_NULL  (GDT_IDX_NULL  * GDT_SZENT)
#define GDT_KCODE (GDT_IDX_KCODE * GDT_SZENT)
#define GDT_KDATA (GDT_IDX_KDATA * GDT_SZENT)
#define GDT_UCODE (GDT_IDX_UCODE * GDT_SZENT)
#define GDT_UDATA (GDT_IDX_UDATA * GDT_SZENT)

#define GDT_PRESENT 	(bit(7))
/* 
 * 5 and 6 bits are rights
 */
#define GDT_PRIV(x)	(bitoff(x, 5))
/* 
 * CORD - code or data
 */
#define GDT_CORD	(bit(4))
#define GDT_CODE	(bit(3))

#define GDT_GROW_DOWN	(bit(2))
#define GDT_PRIV_PUBLIC (bit(2))

#define GDT_READABLE	(bit(1))
#define GDT_WRITEABLE	(bit(1))

#define GDT_GRANULARITY (bit(3))
#define GDT_PROTMODE	(bit(2))
#define GDT_LONGMODE	(bit(1))

#ifndef __ASSEMBLY__

#include <fubos/compiler_attributes.h>
#include <fubos/ints.h>

#define gdt_make_entry(_base, _limit, _access, _flags)			\
	{								\
		.limit_low 	= bitcut(_limit, 0, 16),		\
		.base_low 	= bitcut(_base, 0, 16),			\
		.base_mid	= bitcut(_base, 16, 8),			\
		.access 	= _access,				\
		.flags		= (_flags << 4) | bitcut(_limit, 16, 4),\
		.base_high	= bitcut(_base, 24, 8)			\
	}

struct gdt_entry{
	u16 limit_low;
	u16 base_low;
	u8 base_mid;
	u8 access;
	u8 flags;
	u8 base_high;
} __packed;

__ASSERT(GDT_SZENT == sizeof(struct gdt_entry));

struct gdt_ptr{
	u16 size;
	u32 ptr;
} __packed;

extern struct gdt_ptr 	gdt_ptr;
extern struct gdt_entry gdt[GDT_NENT];

#endif /*  __ASSEMBLY__ */
#endif /* __H_GDT_H */
