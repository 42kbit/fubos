#ifndef   __H_FUBOS_BOOT_H
#define   __H_FUBOS_BOOT_H

/* Meanwhile booting is arch and boot specification dependent, it all comes to kmain
 */
struct boot_info {
};

__noreturn
void kmain (struct boot_info* info);

#endif /* __H_FUBOS_BOOT_H */
