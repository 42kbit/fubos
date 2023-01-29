TMOD	:=$(bd)/tmod

ASMOBJS_$(d)	:=$(od)/test.o

OBJS_$(d)	:=$(ASMOBJS_$(d))

$(call append,TGT_ETC,$(d))

$(d): $(TMOD)
$(TMOD): $(OBJS_$(d))
$(TMOD):
	$(L_LINK)
