#include "klog.h"

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
