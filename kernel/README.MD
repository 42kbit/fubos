
Rules.mk <- subdirectory makefile

lib/	<- c library functions needed for kernel, some files
	may be replaced at some point with static linkage from other
	directory. Some functions like kprintf will stay here,
	since they are part of kernel anyway.

arch/	<- arch dependend code goes here. Arch selected from your
	Makefile.config file (generated upon first make run).

kmain.c	 <- Kernel Main, while entry point of kernel is arch
	dependent, this is where execution will be at some point.

kheap.c  <- Kernel Heap, implementation of malloc, free, in kernel
	memory space (now very simplified since there is no paging).
