#include <fubos/stdarg.h>
#include <fubos/stddef.h>

#include <fubos/kheap.h>
#include <fubos/klog.h>

#include <fubos/types.h>

char * klog_buffer;
off_t klog_buffer_off;

int init_klog_buffer(){
	if ((klog_buffer = (char*)kmalloc(KLOG_BUFFER_LEN)) == NULL){
		/* this should never fail, but if it is... */
		return -1;
	}
	klog_buffer_off = 0;
	return 0;
}

void __klog_buffer_flush();

void kputc	(char c){
	klog_buffer[(klog_buffer_off++) % KLOG_BUFFER_LEN] = c;
#ifdef CONFIG_LOG_INPLACE 
	/* arch dependent 
	 * x86 - vga.c
	 */
	__klog_buffer_flush();
#else
	/* send msg to driver or some shit */
#error "Not supported yet"
#endif
}

char klog_getc_at	(off_t index){
	return klog_buffer[index % KLOG_BUFFER_LEN];
}

static inline size_t __kfmt_len(const char* fmt){
	return 0;
}

int kvsnprintf	(char * buf, size_t size, const char * fmt, va_list args)
{
	typedef enum fmt_state {
		NONE,
		OPERAND
	} fmt_state_t;

	fmt_state_t fmts = NONE;

	const char * fmt_iter;
	char * buf_iter = buf;
	for (fmt_iter = fmt; *fmt_iter != '\0' || ((ptrdiff_t)(buf_iter - buf) < size); fmt_iter++, buf_iter++){
		switch (*fmt_iter){
			default:
				*buf_iter = *fmt_iter;
				break;
		}
	}
	buf[size] = '\0';
	return (int)(fmt_iter - fmt);
}

#define KPRINTF_MAX_LEN 0xff

int kvsprintf	(char * dst, const char * fmt, va_list args){
	return kvsnprintf (dst, KPRINTF_MAX_LEN, fmt, args);
}

int ksprintf	(char * dst, const char * fmt, ...){
	va_list args;
	va_start (args, fmt);

	int val = kvsprintf(dst, fmt, args);

	va_end (args);
	return val;
}

static inline void* _memset (void * dst, char n, size_t len){
	for (int i = 0; i < len; i++){
		((char*)dst)[i] = n;
	}
	return dst;
}

int kvprintf	(const char * fmt, va_list args){
	char str[KPRINTF_MAX_LEN];
	/* TODO: need memset but later*/
	int written;
	written = kvsnprintf (str, KPRINTF_MAX_LEN, fmt, args);
	
	for (const char * i = str; *i != '\0'; i++){
		kputc(*i);
	}
	return written;
}

int kprintf	(const char * fmt, ...){
	va_list args;
	va_start (args, fmt);

	int val = kvprintf(fmt, args);

	va_end (args);
	return val;
}
