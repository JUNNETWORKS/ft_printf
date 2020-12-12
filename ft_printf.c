// 適当にががーっと書くft_printf

/* メモ
 *   処理としては大きく分けて2つある.
 *     1. %から変換指定子までの情報を格納する処理
 *     2. 格納した情報を元に出力する処理
 */
#include "ft_printf.h"
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

int ft_printf(const char *format, ...)
{
	// stdout に書き込んだ文字数
	int write_size;

	write_size = 0;
	va_list ap;
	va_start(ap, format);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			write_size += parse_and_write(ap, &format);
		}
		else
		{
			write_size += write(1, format, 1);
			format++;
		}
	}
	return (write_size);
}

// %の次の文字にポインタはセットされている
int parse_and_write(va_list ap, const char **format)
{
	int write_size;
	write_size = 0;

	t_fmt *fmt_data = new_t_fmt();

	// Flag
	parse_flag(format, fmt_data);
	// width
	parse_width(format, fmt_data, ap);
	// precision
	parse_precision(format, fmt_data, ap);
	// type
	parse_type(format, fmt_data);
	
	printf("\tflag: %d\n\twidth_opt: %d\n\twidth: %lld\n\tprecision: "
	       "%lld\n\ttype: %d\n",
	       fmt_data->flag, fmt_data->width_opt, fmt_data->width,
	   fmt_data->precision, fmt_data->type);
	

	// 実際にstdoutに書き込む
	write_size += write_fmt_data(fmt_data, ap);

	free(fmt_data);
	return (write_size);
}

int write_fmt_data(t_fmt *fmt_data, va_list ap)
{
	if (fmt_data->type == TYPE_PERCENT)
		return (write_percent(fmt_data));
	if (fmt_data->type == TYPE_CHAR)
		return (write_char(fmt_data, ap));
	else if (fmt_data->type == TYPE_STRING)
		return (write_string(fmt_data, ap));
	else if (fmt_data->type == TYPE_UINT || fmt_data->type == TYPE_HEX_LOW || fmt_data->type == TYPE_HEX_UP)
	{
		long long n = va_arg(ap, long long);
		return (write_integer(fmt_data, n));
	}
	else if (fmt_data->type == TYPE_INT)
	{
		long long n = va_arg(ap, int);
		return (write_integer(fmt_data, n));
	}
	else if (fmt_data->type == TYPE_POINTER)
	{
		long long n = va_arg(ap, long long);
		return (write_integer(fmt_data, n));
	}
	return (0);
}
