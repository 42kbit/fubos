COBJS_$(d)	:=$(od)/multiboot_header.o
ASMOBJS_$(d)	:=$(od)/entry.o
OBJS_$(d)	:=	\
	$(ASMOBJS_$(d))	\
	$(COBJS_$(d))

LF_$(KBIN)	:=\
		-T $(od)/prep_multiboot2.ld\
		-Map=$(dir $(KBIN))/kmap.map

$(KBIN): $(OBJS_$(d)) $(od)/prep_multiboot2.ld

$(od)/prep_multiboot2.ld: $(d)/multiboot2.ld
	$(CC) -E -P -x c $(CF_ALL) -D__GNULD__=1 $^ > $@
