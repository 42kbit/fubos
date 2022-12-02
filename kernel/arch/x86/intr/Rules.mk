
COBJS_$(d)	:=		\
	$(od)/idt.o		\
	$(od)/cisr.o		\
	$(od)/pic.o 		

ASMOBJS_$(d)	:=		\
	$(od)/isr.o

OBJS_$(d)	:=$(COBJS_$(d)) $(ASMOBJS_$(d))

SUBDIRS_$(d)	:=handlers

$(KBIN):	$(OBJS_$(d))
