#ifndef __H_FUBOS_STRING_H
#define __H_FUBOS_STRING_H

#include <fubos/stddef.h>

void * memcpy (void * dst, const void * src, size_t size);
void * memset (void * dst, int c, size_t size);
size_t strlen (const char * str);

char * strncat (char * s1, const char * s2, size_t s);
char * strcat (char * s1, const char * s2);

void __strncat_len(char* s1, const char * s2, size_t s,
		size_t * s1_len, size_t * was_written);

#endif /* __H_FUBOS_STRING_H*/
