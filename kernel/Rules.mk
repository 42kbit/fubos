KBIN	:=$(bd)/kernel.bin

COBJS_$(d)	:=$(od)/kmain.o
OBJS_$(d)	:=$(COBJS_$(d))

$(call append,TGT_ETC,$(d))

TGTS_$(d) 	:=$(KBIN)

LF_$(KBIN) += -Map=$(bd)/kbin.map

$(d): $(KBIN)
$(KBIN): $(COBJS_$(d))
$(KBIN):
	$(L_LINK)

SUBDIRS_$(d)	:=arch
