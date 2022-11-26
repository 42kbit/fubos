#ifndef __H_FUBOS_KLOG_H
#define __H_FUBOS_KLOG_H

#include <fubos/stdarg.h>
#include <fubos/page.h>
#include <fubos/types.h>

extern char * klog_buffer;
extern off_t klog_buffer_off;

#define KLOG_BUFFER_LEN PAGE_SIZE

int init_klog_buffer	(void);
char klog_getc_at	(off_t);

void kputc	(char c);

int kvsprintf	(char * restrict, const char * fmt, va_list args);
int ksprintf	(char * restrict, const char * fmt, ...);
int kvprintf	(const char * fmt, va_list args);
int kprintf	(const char * fmt, ...);

#endif /* __H_FUBOS_KLOG_H */
