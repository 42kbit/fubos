#ifndef __H_FUBOS_INCLUDE_FUBOS_ALIGNMENT_H
#define __H_FUBOS_INCLUDE_FUBOS_ALIGNMENT_H

#define align(x, to) ((x + (to - 1)) & ~(to - 1))
#define padding(x,to) (align(x,to)-x)

#endif /* __H_FUBOS_INCLUDE_FUBOS_ALIGNMENT_H */
