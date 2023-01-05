#ifndef __H_FUBOS_LIMITS_H
#define __H_FUBOS_LIMITS_H

#include <fubos/assert.h>

__ASSERT(sizeof(int) == 4);

#define UINT_MAX 0xffffffff

#define INT_MAX 0x7fffffff
#define INT_MIN (-INT_MAX - 1)

#endif /* __H_FUBOS_LIMITS_H */
