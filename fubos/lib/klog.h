#ifndef __H_LIB_KLOG_H
#define __H_LIB_KLOG_H

#include <fubos/stdarg.h>
#include <fubos/stddef.h>
#include <fubos/string.h>

#include <fubos/kheap.h>
#include <fubos/klog.h>

#include <fubos/types.h>
#include <fubos/limits.h>
#include <fubos/errno.h>

#define KPRINTF_MAX_LEN 0x7ff

extern char * klog_buffer;
extern off_t klog_buffer_off;

#endif
