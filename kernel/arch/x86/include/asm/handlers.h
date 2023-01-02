#ifndef   __H_HANDLERS_H
#define   __H_HANDLERS_H

#include <asm/isr.h>

/*
 * kernel/intr/handlers/page_fault.c
 */
void on_page_fault (struct isr_regs*);

#endif /* __H_HANDLERS_H */
