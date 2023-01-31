/* Pointer arithmetic header
 */
#ifndef   __H_PMATH_H
#define   __H_PMATH_H

#include <fubos/types.h>
#include <fubos/alignment.h>

/* offset pointer 'x' by 'val' bytes and cast it to 'type',
 * and align by 'alignment'
 */
#define ptraddca(ptr, offset, type, alignment)\
	((type)align((addr_t)((addr_t)ptr+(offset)), alignment))

/* offset pointer 'x' by 'val' bytes and cast it to 'type'
 */
#define ptraddc(ptr, offset, type)\
	ptraddca(ptr, offset, type, 1)

/* offset pointer 'x' by 'val' bytes
 */
#define ptradd(ptr, offset)\
	ptraddc(ptr, offset, typeof(x))

#endif /* __H_PMATH_H */
