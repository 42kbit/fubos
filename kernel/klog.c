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
	for (fmt_iter = fmt; *fmt_iter != '\0'; fmt_iter++, buf_iter++){
		switch (*fmt_iter){
			case '%':
				if (fmts == OPERAND)
					*buf_iter = '%';
				else 
					fmts = OPERAND;
				break;
		}
	}
	return (int)(fmt_iter - fmt);
}

int kvsprintf	(char * dst, const char * fmt, va_list args){
	return 0;
}

int ksprintf	(char * dst, const char * fmt, ...){
	va_list args;
	va_start (args, fmt);

	int val = kvsprintf(dst, fmt, args);

	va_end (args);
	return val;
}

int kvprintf	(const char * fmt, va_list args){
	for (const char * i = fmt; *i != '\0'; i++){
		kputc(*i);
	}
	return 0;
}

int kprintf	(const char * fmt, ...){
	va_list args;
	va_start (args, fmt);

	int val = kvprintf(fmt, args);

	va_end (args);
	return val;
}
