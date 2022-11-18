
COBJS_$(d)	:=		\
	$(od)/gdt.o 		\
	$(od)/idt.o		\
	$(od)/arch_spec.o	

ASMOBJS_$(d)	:=		\
	$(od)/seg_reload.o	\
	$(od)/isr.o

OBJS_$(d)	:=$(COBJS_$(d)) $(ASMOBJS_$(d))

SUBDIRS_$(d)	:=stand

$(KBIN):	$(OBJS_$(d))
