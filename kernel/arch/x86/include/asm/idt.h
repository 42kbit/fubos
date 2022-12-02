#ifndef __H_IDT_H
#define __H_IDT_H

#include <fubos/bitops.h>

#define IDT_NENT 	256

#define IDT_GT_TASK	0x5
#define IDT_GT_16_INTR 	0x6
#define IDT_GT_16_TRAP 	0x7

#define IDT_GT_32_INTR 	0xe
#define IDT_GT_32_TRAP 	0xf

#ifndef __ASSEMBLY__

#include <fubos/ints.h>
#include <fubos/compiler_attributes.h>

#define idt_make_entry(_handler, _selector, _gtype, _dpl, _p)\
	{\
		.offset 	= bitcut(_handler, 0, 16),\
		.selector 	= _selector,\
		.__reserved	= 0,\
		.gt		= _gtype,\
		.__zero 	= 0,\
		.dpl		= _dpl,\
		.p		= _p,\
		.offset_high	= bitcut(_handler, 16, 16)\
	}

struct idt_entry {
	u16 offset;
	u16 selector;
	u8  __reserved;
	u8  gt		: 4,
	    __zero	: 1,
	    dpl		: 2,
	    p		: 1;
	u16 offset_high;
} __packed;

struct idt_ptr {
	u16 size;
	u32 ptr;
} __packed;

extern struct idt_entry idt[IDT_NENT];
extern struct idt_ptr	idt_ptr;

void flush_idt (struct idt_ptr*);

void idt_load_entry ( 
		struct idt_entry* table,
		u8 where,
		u32 handler,
		u16 selector,
		u8 gt,
		u8 dpl,
		u8 present );

#endif /* __ASSEMBLY__ */
#endif /* __H_IDT_H */
