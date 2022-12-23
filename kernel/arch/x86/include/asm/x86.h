#ifndef __H_X86_H
#define __H_X86_H

#ifndef __ASSEMBLY__

#include <fubos/ints.h>

/* register get/set recepie
 * 
 * Generates following:
 * x - register name
 * s - at&t asm operand "mov"#s (movb, movw, movl)
 * var - location write/read from
 *
 * __x86_reg_get(ds,w,seg,rm) expands to
 * asm volatile("movw %%ds, %%0" : =rm(seg))
 * */
#define __x86_reg_set(x, s, var, mode)\
	asm volatile("mov" #s " %0,%%" #x : : #mode(var)) 

#define __x86_reg_get(x, s, var, mode)\
	asm volatile("mov" #s " %%" #x ",%0" : "="#mode(var))

#define __make_reg_getter(reg, prefix, type, mode)	\
	static inline type get_##reg (void){		\
		type r;					\
		__x86_reg_get(reg, prefix, r, mode);	\
		return r;				\
	}

#define __make_reg_setter(reg, prefix, type, mode)	\
	static inline void set_##reg (type r){		\
		__x86_reg_set(reg, prefix, r, mode);	\
	}

#define __make_reg_all(reg, prefix, type, mode)		\
	__make_reg_getter(reg, prefix, type, mode);	\
	__make_reg_setter(reg, prefix, type, mode)

/* 
 * 	Source
 * 	https://wiki.osdev.org/Inline_Assembly
 */
static inline u8 inb (u16 port){
    u8 val;
    asm volatile("inb %1, %0" : "=a"(val) : "Nd"(port));
    return val;
}

static inline void outb (u16 port, u8 value){
    asm volatile("outb %0, %1" :: "r"(value), "r"(port));
}

__make_reg_all(eax, l, u32, rm);
__make_reg_all(ebx, l, u32, rm);
__make_reg_all(ecx, l, u32, rm);
__make_reg_all(edx, l, u32, rm);

__make_reg_all(ax, w, u16, rm);
__make_reg_all(bx, w, u16, rm);
__make_reg_all(cx, w, u16, rm);
__make_reg_all(dx, w, u16, rm);

__make_reg_all(al, b, u8, rm);
__make_reg_all(ah, b, u8, rm);
__make_reg_all(bl, b, u8, rm);
__make_reg_all(bh, b, u8, rm);
__make_reg_all(cl, b, u8, rm);
__make_reg_all(ch, b, u8, rm);
__make_reg_all(dl, b, u8, rm);
__make_reg_all(dh, b, u8, rm);

__make_reg_all(ds, w, u16, rm);
__make_reg_all(es, w, u16, rm);
__make_reg_all(fs, w, u16, rm);
__make_reg_all(gs, w, u16, rm);
__make_reg_all(ss, w, u16, rm);

__make_reg_all(cr0, l, u32, a);
__make_reg_all(cr1, l, u32, a);
__make_reg_all(cr2, l, u32, a);
__make_reg_all(cr3, l, u32, a);
__make_reg_all(cr4, l, u32, a);

#endif /* __ASSEMBLY__ */
#endif /* __H_X86_H */
