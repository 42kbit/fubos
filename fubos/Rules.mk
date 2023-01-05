KBIN	:=$(bd)/kernel.bin

COBJS_$(d)	:=\
	$(od)/kmain.o\
	$(od)/kheap.o

OBJS_$(d)	:=$(COBJS_$(d))

$(call append,TGT_ETC,$(d))

TGTS_$(d) 	:=$(KBIN)

LF_$(KBIN) += -Map=$(bd)/kbin.map

# Add for each subdir, starting from current, following compilation flags:
# $(shell find '$(d)' -type d) <- returns list of all sdirs, starting from $(d)

KBIN_INCFLAGS := -I$(d)/include -I$(d)/arch/$(ARCH)/include

# Recrusive CFLAGS, that added for each subdir
RCFLAGS = $(CF_ALL) $(KBIN_INCFLAGS) \
	-nostdlib -nostdinc -fno-builtin

RASFLAGS = $(CF_ALL) $(KBIN_INCFLAGS) \
	-nostdlib -nostdinc -fno-builtin -Xassembler --divide

$(foreach di,\
	$(shell find $(d) -type d),\
	$(eval CF_$(di) += $(RCFLAGS)))

$(foreach di,\
	$(shell find $(d) -type d),\
	$(eval ASF_$(di) += $(RASFLAGS)))

$(d): $(KBIN)
$(KBIN): $(COBJS_$(d))
$(KBIN):
	$(L_LINK)

SUBDIRS_$(d)	:=arch lib
