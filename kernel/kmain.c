/* on this line was a ton of cringe, so i removed it */

#include <asm/gdt.h>
#include <asm/x86.h>

#include <fubos/ints.h>
#include <fubos/bitops.h>
#include <fubos/symbol.h>

/* not arch independent code will be fixed later */
void arch_spec(void);

atr_noret atr_weak void cpu_relax(void){
	while (1);
}

#define __X86_INT(x) asm volatile ( "int $" #x ";" )

extern u32 __isr_proc_len;

void kmain(void){
	/* invoke arch specific preparations */
	arch_spec();

	while (1){
		__X86_INT(0);
		__X86_INT(1);
		__X86_INT(2);
		__X86_INT(3);
		__X86_INT(4);
		__X86_INT(5);
		__X86_INT(6);
		/* ints 7,9,10,11 (and maybe others) cause int 6 for some reason*/
		__X86_INT(8);
	}

	cpu_relax();
}
