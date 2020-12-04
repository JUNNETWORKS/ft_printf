// 適当にががーっと書くft_printf

/* メモ
 *   処理としては大きく分けて2つある.
 *     1. %から変換指定子までの情報を格納する処理
 *     2. 格納した情報を元に出力する処理
 */
#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"
#include <stdio.h>

int parse_and_write(va_list ap, const char**format);

int ft_printf(const char*format, ...)
{
    // stdout に書き込んだ文字数
    int write_size;
    write_size = 0;
    va_list ap;
    va_start(ap, format);

	while (*format)
	{
		if (*format == '%'){
			format++;
			write_size += parse_and_write(ap, &format);
		}
		else{
			// % 以外の場合はそのまま出力する
			write_size += write(1, format, 1);
			format++;
		}
	}
	return (write_size);
}

t_fmt *new_t_fmt()
{
  t_fmt* fmt_data = malloc(sizeof(t_fmt));
  fmt_data->base = 10;
  fmt_data->flag = FLAG_NONE;
  fmt_data->precision = 0;
  fmt_data->type = TYPE_NONE;
  fmt_data->width_opt = WIDTH_OPT_NONE;
  return (fmt_data);
}

// %の次の文字にポインタはセットされている
int parse_and_write(va_list ap, const char**format)
{
	int write_size;
	write_size = 0;

	t_fmt *fmt_data = new_t_fmt();

	// Flag
	while (**format && (**format == '0' || **format == '-')){
	  if (**format == '0')
		fmt_data->flag |= PREPEND_ZEROS;
	  if (**format == '-')
		fmt_data->flag |= LEFT_ALIGNED;
	  (*format)++;
	}
	// width
	// 引数で渡された値をwidthとして使用する
	if (**format == '*'){
	  int width = va_arg(ap, int);
	  if (width < 0){
		fmt_data->flag |= LEFT_ALIGNED;
		width = -width;
	  }
	  fmt_data->width = (unsigned int)width;
	  (*format)++;
	}else if (ft_isdigit(**format)){
	  int width = ft_atoi(*format);
	  fmt_data->width = (unsigned int)width;
	  (*format) += num_len(*format);
	}
	// precision
	if (**format == '.'){
	  (*format)++;
	  if (**format == '*'){
		int precision = va_arg(ap, int);
		if (precision < 0){
		  fmt_data->precision = 0;
		}else{
		  fmt_data->precision = precision;
		};
		(*format)++;
	  }
	  // 負の数が指定された場合は精度の指定は無し
	  else if (**format == '-'){
		(*format)++;
		(*format) += num_len(*format);
	  }
	  // 数字が入力されていた場合
	  else{
		fmt_data->precision = ft_atoi(*format);
		(*format) += num_len(*format);
	  }
	}
	// type
	if (**format == 'd' || **format == 'i')
		fmt_data->type = TYPE_INT;
	else if (**format == 'u')
		fmt_data->type = TYPE_UINT;
	else if (**format == 'x')
		fmt_data->type = TYPE_HEX_LOW;
	else if (**format == 'X')
		fmt_data->type = TYPE_HEX_UP;
	else if (**format == 'c')
		fmt_data->type = TYPE_CHAR;
	else if (**format == 's')
		fmt_data->type = TYPE_STRING;
	else if (**format == 'p')
		fmt_data->type = TYPE_POINTER;
	else if (**format == '%')
		fmt_data->type = TYPE_PERCENT;
	(*format)++;
	// 実際にstdoutに書き込む
	printf("t_fmt\n");
	printf("\tflag: %d\n\twidth_opt: %d\n\twidth: %u\n\tprecision: %zd\n\ttype: %d\n", fmt_data->flag, fmt_data->width_opt, fmt_data->width, fmt_data->precision, fmt_data->type);
	free(fmt_data);
	return (write_size);
}
