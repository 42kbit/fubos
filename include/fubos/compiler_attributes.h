#ifndef __H_FUBOS_COMPILER_ATTRIBUTES_H
#define __H_FUBOS_COMPILER_ATTRIBUTES_H

#define __atr(x)\
	__attribute__((x))

#define __section(name)\
	__atr(section(name))

#define __packed\
	__atr(packed)

#define __noreturn\
	__atr(noreturn)

#define __weak\
	__atr(weak)

#define __aligned(x)\
	__atr(__aligned__(x))

#endif /* __H_FUBOS_SECTIONS_H */
