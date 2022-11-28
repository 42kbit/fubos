#include "klog.h"

char * klog_buffer;
off_t klog_buffer_off;

int init_klog_buffer(){
	if ((klog_buffer = (char*)kmalloc(KLOG_BUFFER_LEN)) == NULL){
		/* this should never fail, but if it is... */
		return -EINVAL;
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

int kvprintf	(const char * fmt, va_list args){
	char str[KPRINTF_MAX_LEN];
	memset(str, 0, KPRINTF_MAX_LEN * sizeof(char));
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
