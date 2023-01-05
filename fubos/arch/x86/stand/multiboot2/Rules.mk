COBJS_$(d)	:=		\
	$(od)/mb2_header.o	\
	$(od)/mb2_entry.o	\
	$(od)/mb2_bootwrap.o
ASMOBJS_$(d)	:=$(od)/entry.o
OBJS_$(d)	:=	\
	$(ASMOBJS_$(d))	\
	$(COBJS_$(d))

CF_$(od)/mb2_entry.o	:=-Wno-unused-parameter

LF_$(KBIN)	:=\
		-T $(od)/prep_mb2.ld\
		-Map=$(dir $(KBIN))/kmap.map

$(KBIN): $(OBJS_$(d)) $(od)/prep_mb2.ld

$(od)/prep_mb2.ld: $(d)/mb2.ld
	$(CC) -E -P -x c $(KBIN_INCFLAGS) -D__GNULD__=1 $^ > $@
