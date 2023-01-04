#ifndef   __H_FUBOS_BOOT_H
#define   __H_FUBOS_BOOT_H

#include <fubos/compiler_attributes.h>

/* Meanwhile booting is arch and boot specification dependent, it all comes to kmain
 */
struct boot_info;

const char * binfo_loader_name (struct boot_info*);

void kmain (struct boot_info* info) __noreturn;

#endif /* __H_FUBOS_BOOT_H */
