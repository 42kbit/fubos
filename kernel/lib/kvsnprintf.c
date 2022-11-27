#include "klog.h"

static inline void reverse_inplace(char * str, size_t len){
	char tmp;
	for (i32 i = 0; i < len/2; i++){
		tmp = str[i];
		str[i] = str[len-i-1];
		str[len-i-1] = tmp;
	}
}

static inline ptrdiff_t utoa (u32 n, char * buf, u8 base, const char* digits){
	char * buf_iter = buf;
	i32 digit;
	while (n != 0){
		digit = n % base;
		n /= base;

		*(buf_iter++) = digits[digit];
	}
	reverse_inplace(buf, strlen(buf));
	return buf_iter - buf;
}

int kvsnprintf	(char * buf, size_t size, const char * fmt, va_list args)
{
	const char * fmt_ptr = fmt;
	char * buf_ptr = buf, c;
	ptrdiff_t diff;

	static const char * digits = "0123456789abcdef";

	while ((c = *(fmt_ptr++))){
		if (c == '%'){
			switch (c = *(fmt_ptr++)){
				case '%':
					*(buf_ptr++) = c;
					break;
				case 'u':
					diff = utoa(va_arg(args, u32), buf_ptr, 10, digits);
					buf_ptr += diff;
					break;
				case 'p':
					diff = utoa(va_arg(args, addr_t), buf_ptr, 16, digits);
					buf_ptr += diff;
					break;
				default:
					break;
			}
		}
		else {
			*(buf_ptr++) = c;
		}
	}
	return buf_ptr - buf;
}
