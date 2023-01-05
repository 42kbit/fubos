#include <fubos/kheap.h>
#include <fubos/symbol.h>

#include <fubos/types.h>

#include <fubos/alignment.h>

extern sym __kheap_begin;
extern sym __kheap_end;

char * __kheap_ptr = __symval(__kheap_begin, char*);

void * kmalloc (size_t n){
	return kmalloc_aligned (n, 1);
}

void * kmalloc_aligned (size_t n, u32 alignment){
	char * kheap_end = __symval(__kheap_end, char*);
	char * kheap_ptr = (char*) align ((addr_t)__kheap_ptr, alignment);
	if ((kheap_ptr + n) > kheap_end){
		/* heap overflow */
		return NULL;
	}
	__kheap_ptr += n + padding((addr_t)__kheap_ptr, alignment);
	return (void*)kheap_ptr;
}

void kfree (void *){
/* 
 * not implemented yet, so does nothing 
 */
}
