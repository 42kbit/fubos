#ifndef   __H_FUBOS_BOOT_H
#define   __H_FUBOS_BOOT_H

struct boot_info {
	void * load_addr;

	int argc;
	const char** argv;
};

extern struct boot_info boot_info;

#endif /* __H_FUBOS_BOOT_H */
