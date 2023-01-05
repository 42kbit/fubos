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

# Following code adds for each directory following c and asm flags.
RCFLAGS = $(CF_ALL) $(KBIN_INCFLAGS) \
	-nostdlib -nostdinc -fno-builtin

RASFLAGS = $(CF_ALL) $(KBIN_INCFLAGS) \
	-nostdlib -nostdinc -fno-builtin -Xassembler --divide

get_subdirs = $(shell find $(1) -type d)
subdirs_append_flags = $(foreach di, $(call get_subdirs, $(1)), $(eval $(2)_$(di) += $(3)) )

$(call subdirs_append_flags, $(d), CF,  $(RCFLAGS) )
$(call subdirs_append_flags, $(d), ASF, $(RASFLAGS))

# Build dependency for kernel image

$(d): $(KBIN)
$(KBIN): $(COBJS_$(d))
$(KBIN):
	$(L_LINK)

SUBDIRS_$(d)	:=arch lib
