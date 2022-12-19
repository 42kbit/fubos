#define __ASSEMBLY__
#include <asm/cr.h>

/*
asm/page.h
void enable_paging (void);
*/
.globl enable_paging
enable_paging:
	movl %cr0, %eax
	orl  $CR0_BIT_PG, %eax
	movl %eax, %cr0
	ret

/*
asm/page.h
void set_page_dir (struct pg_dir* new_dir);
*/

.globl set_page_dir
set_page_dir:
	movl 4(%esp), %eax
	movl %eax, %cr3
	ret
