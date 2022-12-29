#ifndef __H_FUBOS_KLOG_H
#define __H_FUBOS_KLOG_H

#include <fubos/stdarg.h>
#include <fubos/types.h>
#include <fubos/stddef.h>

extern char * klog_buffer;
extern off_t klog_buffer_off;

#define KLOG_BUFFER_LEN 1024

int init_klog_buffer	(void);
char klog_getc_at	(off_t);

void kputc	(char c);

int kvsnprintf	(char * buf, size_t size, const char * fmt, va_list args);
int kvsprintf	(char * buf, const char * fmt, va_list args);
int kvprintf	(const char * fmt, va_list args);
int ksprintf	(char * buf, const char * fmt, ...);
int kprintf	(const char * fmt, ...);

#endif /* __H_FUBOS_KLOG_H */
