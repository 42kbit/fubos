#ifndef __H_FUBOS_KHEAP_H
#define __H_FUBOS_KHEAP_H

#include <fubos/stddef.h>

void * kmalloc (size_t);
void kfree (void *);

#endif /* __H_FUBOS_KHEAP_H */
