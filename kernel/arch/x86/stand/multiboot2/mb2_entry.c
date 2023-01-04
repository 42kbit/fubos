#include <fubos/compiler_attributes.h>
#include <fubos/boot.h>
#include <fubos/alignment.h>

#include <fubos/symbol.h>
#include <fubos/types.h>
#include <fubos/stddef.h>

#include <fubos/klog.h>
#include <fubos/pmath.h>

#include <asm/x86.h>

#include "mb2.h"

/* Set up in entry.S
 */
struct mb2_binfo_header* mb2_binfo = NULL;

static inline struct mb2_binfo_meta* mb2_next_binfo_tag (struct mb2_binfo_meta* current){
	struct mb2_binfo_meta* next;
	if (current == NULL)
		return ptraddc(mb2_binfo, 8, struct mb2_binfo_meta*);
	next = ptraddca(current, current->size, struct mb2_binfo_meta*, 8);
	if (next->type == 0)
		return NULL;
	return next;
}

void mb2_entry (void) {
	__init_vga();
	kprintf ("Info: %p\nTotal size: %u\n", mb2_binfo, mb2_binfo->total_size);
	for (struct mb2_binfo_meta* iter = mb2_next_binfo_tag(NULL);
			iter != NULL;
			iter = mb2_next_binfo_tag(iter))
	{
		kprintf ("%u:%u\n", iter->type, iter->size);
	}
	cpu_die ();
	kmain (NULL);
}
