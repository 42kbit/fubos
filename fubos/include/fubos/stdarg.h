#ifndef __H_FUBOS_INCLUDE_FUBOS_STDARG_H
#define __H_FUBOS_INCLUDE_FUBOS_STDARG_H

typedef __builtin_va_list va_list;

#define va_start(v,l)	__builtin_va_start(v,l)
#define va_end(v)	__builtin_va_end(v)

#define va_arg(v,t)	__builtin_va_arg(v,t)
#define va_copy(d,s)	__builtin_va_copy(d,s)

#endif /* __H_FUBOS_INCLUDE_FUBOS_STDARG_H */
