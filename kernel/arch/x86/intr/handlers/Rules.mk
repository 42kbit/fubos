
COBJS_$(d)	:=		\
	$(od)/page_fault.o

OBJS_$(d)	:=$(COBJS_$(d)) $(ASMOBJS_$(d))

SUBDIRS_$(d)	:=

$(KBIN):	$(OBJS_$(d))
