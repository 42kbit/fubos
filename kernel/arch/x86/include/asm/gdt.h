#ifndef __H_GDT_H
#define __H_GDT_H

#include <fubos/bitops.h>

/* dummy, kernel code/data, user code/data */
#define GDT_NENT 5

#define GDT_NULL  0x0
#define GDT_KCODE 0x08
#define GDT_KDATA 0x10
#define GDT_UCODE 0x18
#define GDT_UDATA 0x20

#define GDT_PRESENT 	(bit(7))
/* 5 and 6 bits are rights */
#define GDT_PRIV(x)	(bitoff(x, 5))
/* CORD - code or data */
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

#define gdt_make_node(_base, _limit, _access, _flags)\
	{\
		.limit_low 	= bitcut(_limit, 0, 16),\
		.base_low 	= bitcut(_base, 0, 16),\
		.base_mid	= bitcut(_base, 16, 8),\
		.a 		= bitcut(_access,0, 1),\
		.rw 		= bitcut(_access,1, 1),\
		.dc		= bitcut(_access,2, 1),\
		.e		= bitcut(_access,3, 1),\
		.s		= bitcut(_access,4, 1),\
		.dpl		= bitcut(_access,5, 2),\
		.p		= bitcut(_access,7, 1),\
		.limit 		= bitcut(_limit, 16, 4),\
		.__reserved 	= bitcut(_flags, 0, 1),\
		.l		= bitcut(_flags, 1, 1),\
		.db		= bitcut(_flags, 2, 1),\
		.g		= bitcut(_flags, 3, 1),\
		.base_high	= bitcut(_base, 24, 8)\
	}

struct gdt_node{
	u16 limit_low;
	u16 base_low;
	u8 base_mid;
	u8 a		: 1,
	   rw		: 1,
	   dc		: 1,
	   e		: 1,
	   s		: 1,
	   dpl		: 2,
	   p		: 1;

	u8 limit 	: 4,
	   __reserved	: 1,
	   l		: 1,
	   db		: 1,
	   g		: 1;
	u8 base_high;
} __packed;

struct gdt_ptr{
	u16 size;
	u32 ptr;
} __packed;

extern struct gdt_ptr gdt_ptr;
extern struct gdt_node gdt[GDT_NENT];

/* seg_reload.S */
void flush_gdt(struct gdt_ptr*);

#endif /*  __ASSEMBLY__ */
#endif /* __H_GDT_H */
