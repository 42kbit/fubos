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
	/* may use container_of, but that is overkill */
	struct mb2_binfo_loadername* base = (struct mb2_binfo_loadername*)_base;
	info->loader_name = base->string;
}

static inline void mb2_binfo_parser_module (struct mb2_binfo_meta* _base, struct boot_info* info){
	struct mb2_binfo_module* base = (struct mb2_binfo_module*)_base;
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

void mb2_entry (void) {
	struct boot_info binfo;

	for (struct mb2_binfo_meta* iter = mb2_next_binfo_tag(NULL);
			iter != NULL;
			iter = mb2_next_binfo_tag(iter))
	{
		mb2_binfo_parser_t iter_parser = mb2_get_parser_func (iter);
		if (iter_parser)
			iter_parser (iter, &binfo);
	}
	kmain (&binfo);
}
