#ifndef __H_BITOPS_H
#define __H_BITOPS_H

/* bit(0) = 0b00000001 */
/* bit(4) = 0b00010000 */
/* bit(5) = 0b00100000 */
/* bit(7) = 0b10000000 */

#define bit(x) (1<<x)

/* bitmask(0) = 0b00000000 */
/* bitmask(4) = 0b00001111 */
/* bitmask(5) = 0b00011111 */
/* bitmask(7) = 0b01111111 */

#define bitmask(x) (bit(x) - 1)

#define bitoff(x, by) (x << by)

/* in "val", from "where" bit, take "by" */

/* val = 1100 0110 
 * bitcut(val, 0, 4) = 0000 0110
 * bitcut(val, 4, 4) = 0000 1100
 * */

#define bitcut(val, where, by) ((val >> where) & bitmask(by))

#define align(x, to) ((x + (to - 1)) & ~(to - 1))
#define padding(x,to) (align(x,to)-x)

#define kib(x) (x * (1<<10))
#define mib(x) (x * (1<<20))
#define gib(x) (x * (1<<30))

#endif
