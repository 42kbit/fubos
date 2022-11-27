#include <fubos/string.h>
#include <fubos/ints.h>

void * memcpy (void * dst, const void * src, size_t size){
	for (u32 i = 0; i < size; i++){
		((u8*)dst)[i] = ((u8*)src)[i];
	}
	return dst;
}

void * memset (void * dst, int c, size_t size){
	for (u32 i = 0; i < size; i++){
		((u8*)dst)[i] = (u8)c;
	}
	return dst;
}
