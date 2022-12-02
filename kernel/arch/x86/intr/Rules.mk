
COBJS_$(d)	:=		\
	$(od)/idt.o		\
	$(od)/handlers.o	\
	$(od)/pic.o 		

ASMOBJS_$(d)	:=		\
	$(od)/isr.o

OBJS_$(d)	:=$(COBJS_$(d)) $(ASMOBJS_$(d))

SUBDIRS_$(d)	:=

$(KBIN):	$(OBJS_$(d))
