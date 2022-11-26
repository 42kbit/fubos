#ifndef __H_FUBOS_TYPES_H
#define __H_FUBOS_TYPES_H

#include <fubos/assert.h>
#include <fubos/ints.h>

typedef unsigned long addr_t;
typedef unsigned int  off_t;
__ASSERT(sizeof(addr_t) == sizeof(void*));

#endif /* __H_FUBOS_TYPES_H */
