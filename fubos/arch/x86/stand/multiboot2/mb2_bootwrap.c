#include "mb2.h"
#include <fubos/boot.h>

const char * binfo_loader_name (struct boot_info* info) {
	return info->loader_name;
}
