
COBJS_$(d)	:=		\
	$(od)/page_fault.o	\
	$(od)/stub.o

OBJS_$(d)	:=$(COBJS_$(d)) $(ASMOBJS_$(d))

SUBDIRS_$(d)	:=

$(KBIN):	$(OBJS_$(d))
