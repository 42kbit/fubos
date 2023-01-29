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

/* Set up in entry.S */
struct mb2_binfo_header* mb2_binfo = NULL;

struct boot_info binfo;

static inline struct mb2_binfo_meta* mb2_next_binfo_tag (struct mb2_binfo_meta* current){
	struct mb2_binfo_meta* next;
	if (current == NULL)
		return ptraddc(mb2_binfo, 8, struct mb2_binfo_meta*);
	next = ptraddca(current, current->size, struct mb2_binfo_meta*, 8);
	if (next->type == 0)
		return NULL;
	return next;
}

static inline void mb2_binfo_parser_loadername (struct mb2_binfo_meta* _base, struct boot_info* info){
	struct mb2_binfo_loadername* base = container_of(_base, struct mb2_binfo_loadername, meta);
	info->loader_name = base->string;
}

static inline void mb2_binfo_parser_module (struct mb2_binfo_meta* _base, struct boot_info* info){
	struct mb2_binfo_module* base = container_of(_base, struct mb2_binfo_module, meta);
	info->modules[info->modules_top++].mb2_module = base;
}

/* Parse current info tag, and write to boot_info */
typedef void (*mb2_binfo_parser_t)(struct mb2_binfo_meta*, struct boot_info* info);

/* O(n) but cached so ok */
static inline mb2_binfo_parser_t mb2_get_parser_func (struct mb2_binfo_meta* from){
	switch (from->type){
		case MB2_BINFO_LOADERNAME:	return mb2_binfo_parser_loadername;
		case MB2_BINFO_MODULE:		return mb2_binfo_parser_module;
	}
	return NULL;
}

#include <fubos/symbol.h>
#include <asm/memmap.h>

extern sym __mb2_binfo_copy;
extern sym __kstack_end;
extern sym __bss_end;

void mb2_entry (void) {
	mb2_binfo = phys_to_virt(mb2_binfo);
	/* Copy mb2 info struct after kernel head and stack, so it wont be overwritten */
	memcpy (__symval(__mb2_binfo_copy, void*), mb2_binfo, mb2_binfo->total_size);
	mb2_binfo = __symval(__mb2_binfo_copy, typeof(mb2_binfo));

	mb2_init_boot_info (&binfo);

	for (struct mb2_binfo_meta* iter = mb2_next_binfo_tag(NULL);
			iter != NULL;
			iter = mb2_next_binfo_tag(iter))
	{
		mb2_binfo_parser_t iter_parser = mb2_get_parser_func (iter);
		if (iter_parser)
			iter_parser (iter, &binfo);
	}
	kprintf("__kstack_end: %p\nmb2_binfo: %p\n", (__symval(__kstack_end, void*)), mb2_binfo);
	kmain (&binfo);
}
