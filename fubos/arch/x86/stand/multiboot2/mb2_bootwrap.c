#include "mb2.h"
#include <fubos/boot.h>

const char * binfo_loader_name (struct boot_info* info) {
	return info->loader_name;
}


/* writes to buf array of pointers to modules (NULL terminated) */
void binfo_mods (struct boot_info* info, struct boot_module** buf){
	int i;
	for (i = 0; i < info->modules_top; i++){
		buf[i] = &(info->modules[i]);
	}
	buf[i] = NULL;
}

void* bmod_addr (struct boot_module* mod){
	return mod->mb2_module->mod_start;
}

const char* bmod_name (struct boot_module* mod){
	return &(mod->mb2_module->string);
}
