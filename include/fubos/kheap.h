#ifndef __H_FUBOS_KHEAP_H
#define __H_FUBOS_KHEAP_H

#include <fubos/stddef.h>
#include <fubos/ints.h>

void * kmalloc (size_t);

void * kmalloc_aligned (size_t, u32);

void kfree (void *);

#endif /* __H_FUBOS_KHEAP_H */
