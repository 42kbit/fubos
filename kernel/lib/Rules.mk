COBJS_$(d)	:=\
	$(od)/klog.o\
	$(od)/kvsnprintf.o

OBJS_$(d)	:=$(COBJS_$(d))

$(d): $(KBIN)
$(KBIN): $(OBJS_$(d))
