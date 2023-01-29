#ifndef   __H_FUBOS_BOOT_H
#define   __H_FUBOS_BOOT_H

#include <fubos/compiler_attributes.h>
#include <fubos/stddef.h>

#define BOOT_MAX_MODS 32

/* Meanwhile booting is arch and boot specification dependent, it all comes to kmain,
 * after basic kernel preparation, like setting up virtual memory for high kernel.
 */
struct boot_info;
struct boot_module;

const char* binfo_loader_name 	(struct boot_info*);
/* returns NULL terminated array of pointers to modules */
void  binfo_mods (struct boot_info*, struct boot_module**);

const char* bmod_name (struct boot_module*);
void* bmod_addr (struct boot_module*);

void kmain (struct boot_info* info) __noreturn;

#endif /* __H_FUBOS_BOOT_H */
