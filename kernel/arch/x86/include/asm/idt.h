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

#define IDT_FLAGS_SHIFT_P	7
#define IDT_FLAGS_SHIFT_DPL	5

#define idt_make_entry(_handler, _selector, _gtype, _dpl, _p)\
	{\
		.offset 	= bitcut(_handler, 0, 16),\
		.selector 	= _selector,\
		.__reserved	= 0,\
		.flags		= _gtype | (_dpl << IDT_FLAGS_SHIFT_DPL) | (_p << IDT_FLAGS_SHIFT_P),\
		.offset_high	= bitcut(_handler, 16, 16)\
	}

struct idt_entry {
	u16 offset;
	u16 selector;
	u8  __reserved;
	u8 flags;
	u16 offset_high;
} __packed;

static inline u32 idt_entry_offset (const struct idt_entry * ent){
	return ((ent->offset_high << 16) | ent->offset);
}

static inline u16 idt_entry_selector (const struct idt_entry * ent){
	return ent->selector;
}

static inline u8 idt_entry_gt (const struct idt_entry * ent){
	return bitcut(ent->flags, 0, 4);
}

static inline u8 idt_entry_dpl (const struct idt_entry * ent){
	return bitcut(ent->flags, IDT_FLAGS_SHIFT_DPL, 2);
}

static inline u8 idt_entry_p (const struct idt_entry * ent){
	return bitcut(ent->flags, IDT_FLAGS_SHIFT_P, 1);
}

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
