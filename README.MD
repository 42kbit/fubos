FUBOS (No Rights Reserved)

This shit-kernel posted under CC0 (public domain), so if you need some code from it,
use it as you wish, no need to mention or some other shit :/

 include  <- .h files (for now only kernel)

 kernel 	 <- Sources of kernel

 cfg	 <- Used by build system

 scripts  <- Scripts to do all sorts of thing
 
 LICENSE  <- Linceses, used to distribute this software

 Makefile <- Top level Makefile, use "make" to build everything.
 		(Works with *NIX systems / GCC compiler)
 
 README.MD <- This file
	
For further details, see each dir README.MD

Build guideline
 1. Run "make" in root of the project. (or make -j NUM_OF_THREADS, to build multithreaded)
        This would build the system in the (by default) .out directory.
 2. Run "./scripts/make-grub-iso.sh"
 	This would create grub compatible iso image (recomended with multiboot2 stands)
 
 If you want to run system with qemu, there is a handy script in scripts/qemu-run-iso.sh

Updated:
December 2-nd 2022
