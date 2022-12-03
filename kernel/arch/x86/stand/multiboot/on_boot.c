#include <fubos/compiler_attributes.h>
#include <fubos/boot_info.h>
#include "multiboot.h"

/*
struct boot_info {
	void * load_addr;

	int argc;
	const char** argv;
};
*/

/* definition in include/fubos/boot_info.h */
struct boot_info boot_info;

/* kernel/kmain.c */
void kmain	(void);

/* kernel/kmain.c */
__noreturn
void cpu_die	(void);

__noreturn
void on_boot(void){
	kmain();
	cpu_die();
}
