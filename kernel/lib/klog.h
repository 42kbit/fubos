#ifndef __H_LIB_KLOG_H
#define __H_LIB_KLOG_H

#include <fubos/stdarg.h>
#include <fubos/stddef.h>

#include <fubos/kheap.h>
#include <fubos/klog.h>

#include <fubos/types.h>

#define KPRINTF_MAX_LEN 0xff

extern char * klog_buffer;
extern off_t klog_buffer_off;

#endif
