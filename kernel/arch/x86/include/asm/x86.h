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
 * __x86_reg_get(ds,w,seg) expands to
 * asm volatile("movw %%ds, %%0" : =rm(seg))
 * */
#define __x86_reg_set(x, s, var)\
	asm volatile("mov" #s " %0,%%" #x : : "rm"(var)) 

#define __x86_reg_get(x, s, var)\
	asm volatile("mov" #s " %%" #x ",%0" : "=rm"(var))

/* register getters */
#define __x86_reg16_get(x, var)\
	__x86_reg_get(x,w,var)

#define __x86_reg32_get(x, var)\
	__x86_reg_get(x,l,var)

/* register setters */
#define __x86_reg16_set(x, var)\
	__x86_reg_set(x,w,var)

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

static inline u16 ds(void)
{
	u16 seg;
	__x86_reg16_get(ds,seg);
	return seg;
}

static inline void set_ds(u16 seg)
{
	__x86_reg16_set(ds,seg);
}

static inline u16 fs(void)
{
	u16 seg;
	__x86_reg16_get(fs,seg);
	return seg;
}

static inline void set_fs(u16 seg)
{
	__x86_reg16_set(fs,seg);
}

static inline u16 es(void)
{
	u16 seg;
	__x86_reg16_get(es,seg);
	return seg;
}

static inline void set_es(u16 seg)
{
	__x86_reg16_set(es,seg);
}

static inline u16 gs(void)
{
	u16 seg;
	__x86_reg16_get(gs,seg);
	return seg;
}

static inline void set_gs(u16 seg)
{
	__x86_reg16_set(gs,seg);
}

static inline u32 cr0(){
	u32 seg;
	__x86_reg32_get(cr0, seg);
	return seg;
}

static inline u32 cr4(){
	u32 seg;
	__x86_reg32_get(cr4, seg);
	return seg;
}

#endif /* __ASSEMBLY__ */
#endif /* __H_X86_H */
