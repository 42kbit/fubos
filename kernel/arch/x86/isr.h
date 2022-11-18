#ifndef __H_ISR_H
#define __H_ISR_H

#ifdef __ASSEMBLY__
#undef __ASSEMBLY__
#else

#include <fubos/symbol.h>

struct isr_regs {
	u32 ds : 16, __unused : 16; /* lower 16 bits are old ds segment */
	u32 edi, esi, ebp, esp, ebx, edx, ecx, eax; /* pusha */
	u32 intno, errno; /* pushed by first stage intr handler (check isr.S),
			       or dummy if hardware does not push errcode*/
	u32 eip, cs, eflags, useresp, ss; /* pushed by hardware */
};
typedef struct isr_regs isr_regs_t;

void isr0	(void);

extern sym __isr_proc_len;

/*
 * ok so idea here is that each isr is the same size,
 * 	pushb $err_code
 * 	pushb $isr_num
 * 	jmp isr_stub
 */

#define isr_addr(n) (void(*)(isr_regs_t*))((char*)isr0 + n * symval(__isr_proc_len))

#endif /* __ASSEMBLY */
#endif /* __H_ISR_H */
