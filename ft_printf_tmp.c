// 適当にががーっと書くft_printf
#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"

int ft_printf(const char*format, ...);

int ft_printf(const char*format, ...)
{
    // stdout に書き込んだ文字数
    int write_size;
    write_size = 0;
    va_list ap;
    va_start(ap, format);

	while (format)
	{
		if (*format == '%'){
			format++;
			write_size += parse_and_write(ap, &format);
		}
		else{
			// % 以外の場合はそのまま出力する
			write_size += write(1, format, 1);
		}
	}
	return (write_size);
}

// %の次の文字にポインタはセットされている
int parse_and_write(va_list ap, const char**format)
{
	int write_size;
	write_size = 0;

	t_fmt fmt_data;

	// Flag
	while (**format && (**format == '0' || **format == '-')){
	  if (**format == '0')
		fmt_data.flag |= PREPEND_ZEROS;
	  if (**format == '-')
		fmt_data.flag |= LEFT_ALIGNED;
	  (*format)++;
	}
	// width
	// 引数で渡された値をwidthとして使用する
	if (**format == '*'){
	  fmt_data.width = -1;
	}
	// precision
	// modifier
	// type
	
	// 実際にstdoutに書き込む
}
