#include "klog.h"

#include <fubos/assert.h>

static inline void reverse_inplace(char * str, size_t len){
	char tmp;
	for (i32 i = 0; i < len/2; i++){
		tmp = str[i];
		str[i] = str[len-i-1];
		str[len-i-1] = tmp;
	}
}

static inline ptrdiff_t __psize (addr_t num){
	ptrdiff_t len = 0;
	while (num != 0){
		len++;
		num /= 16;
	}
	return len;
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
	if ((buf_iter - buf) == 0)
		*(buf_iter++) = '0';
	return buf_iter - buf;
}

int kvsnprintf	(char * buf, size_t size, const char * fmt, va_list args)
{
	return_val_if (fmt == NULL, -EINVAL);

	const char * fmt_ptr = fmt;
	char * buf_ptr = buf, c;
	ptrdiff_t diff;

	static const char * digits = "0123456789abcdef";

	while ((c = *(fmt_ptr++)) && size-- > 0){
		if (c != '%'){
			*(buf_ptr++) = c;
			continue;
		}

		switch (c = *(fmt_ptr++)){
			case '%':
				*(buf_ptr++) = c;
				break;

			case 'u':
				diff = utoa(va_arg(args, u32), buf_ptr, 10, digits);
				buf_ptr += diff;
				break;
			case 'p':
			case 'h':
				addr_t addr = va_arg(args, addr_t);
				__strncat_len(buf_ptr, "0x", 2, NULL, (size_t*)&diff);
				buf_ptr += diff;
				if (c == 'p'){
					int padding = (sizeof(void*)*2) - __psize(addr);
					memset (buf_ptr, '0', padding);
					buf_ptr += padding;
				}
				diff = utoa(addr, buf_ptr, 16, digits);
				buf_ptr += diff;
				break;
			case 's':
				__strncat_len(buf_ptr, va_arg(args, const char*), INT_MAX, NULL, (size_t*)&diff);
				buf_ptr += diff;
				break;
			default:
				break;
		}
	}
	return buf_ptr - buf;
}
