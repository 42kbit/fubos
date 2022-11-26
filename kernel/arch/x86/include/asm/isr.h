#ifndef __H_ISR_H
#define __H_ISR_H

#define IRQ0	0x20
#define IRQ15	0x2f
#define IRQ(n)	(IRQ0 + n)

#ifndef __ASSEMBLY__

/*
 * 	ISR MAP
 *
 * 	CPU Exceptions 	0-31	(0x0-0x1f)
 *
 * 	PIC Interrupts 	32-47	(0x20-0x2f)
 * 		Master 	32-39	(0x20-0x27)
 * 		Slave  	40-47	(0x28-0x2f)
 *
 * 	Free		47-255	(0x30-0xff)
 *
 */

#include <fubos/stddef.h>
#include <fubos/symbol.h>
#include <asm/idt.h>

struct isr_regs {
	u32 ds : 16, __unused : 16; /* lower 16 bits are old ds segment */
	u32 edi, esi, ebp, esp, ebx, edx, ecx, eax; /* pusha */
	u32 intno, errno; /* pushed by first stage intr handler (check isr.S),
			       or dummy if hardware does not push errcode*/
	u32 eip, cs, eflags, useresp, ss; /* pushed by hardware */
};
typedef struct isr_regs isr_regs_t;

/* isr.S */
void isr0	(void);

extern sym __isr_proc_align;

typedef void (*intr_handler_t) (isr_regs_t*);

extern intr_handler_t intr_handlers[IDT_NENT];

void reg_handler(u8 intno, intr_handler_t);

/*
 * ok so idea here is that each isr is aligned for
 * &__isr_proc_align (proc itself takes around 9 bytes),
 * we can abuse it (isr_addr) to have easy access to needed irq
 */

#define isr_addr(n) (void(*)(isr_regs_t*))((char*)isr0 + n * __symval(__isr_proc_align, size_t))

#define isr_is_irq(isrn)	(isrn >= IRQ0 && isrn <= IRQ15)

#define irq_is_slave(irqn)	(irqn >= 40)

#define isr_to_irq(isrn)	(isrn - IRQ(0))

#endif /* __ASSEMBLY */
#endif /* __H_ISR_H */
