#ifndef __H_FUBOS_SECTIONS_H
#define __H_FUBOS_SECTIONS_H

#define atr(x)\
	__attribute__((x))

#define atr_sec(name)\
	atr(section(name))

#define atr_packed\
	atr(packed)

#define atr_noret\
	atr(noreturn)

#define atr_weak\
	atr(weak)

#endif /* __H_FUBOS_SECTIONS_H */
