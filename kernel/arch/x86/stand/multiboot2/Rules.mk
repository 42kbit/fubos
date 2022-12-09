COBJS_$(d)	:=$(od)/on_boot.o
ASMOBJS_$(d)	:=$(od)/entry.o
OBJS_$(d)	:=	\
	$(ASMOBJS_$(d))	\
	$(COBJS_$(d))

LF_$(KBIN)	:=\
		-T $(d)/multiboot2.ld\
		-Map=$(dir $(KBIN))/kmap.map

$(KBIN): $(OBJS_$(d)) $(d)/multiboot2.ld
