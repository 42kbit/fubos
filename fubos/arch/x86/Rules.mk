
COBJS_$(d)	:=		\
	$(od)/gdt.o 		\
	$(od)/arch_spec.o	

ifneq ($(filter CONFIG_LOG_INPLACE,$(.VARIABLES)),)
COBJS_$(d)	+=$(od)/vga.o
else
$(error CONFIG_LOG_INPLACE disabled (feature not supported yet))
endif

ASMOBJS_$(d)	:=		\
	$(od)/seg_reload.o	

OBJS_$(d)	:=$(COBJS_$(d)) $(ASMOBJS_$(d))

SUBDIRS_$(d)	:=stand intr

$(KBIN):	$(OBJS_$(d))
