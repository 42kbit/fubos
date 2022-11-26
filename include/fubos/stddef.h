#ifndef __H_FUBOS_STDDEF_H
#define __H_FUBOS_STDDEF_H

#define NULL ((void*)0)

typedef unsigned long size_t;

#define offsetof(type,name)\
	( (size_t)&(((type*)0)->name) )

#define container_of(ptr, type, name) \
	( (type*)((char*)ptr - offsetof(type,name)) )

#endif /* __H_FUBOS_STDDEF_H */
