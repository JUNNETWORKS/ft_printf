/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 01:03:47 by jtanaka           #+#    #+#             */
/*   Updated: 2020/12/10 07:19:01 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

void parse_flag(const char **format, t_fmt *fmt_data)
{
	while (**format && (**format == '0' || **format == '-'))
	{
		if (**format == '0')
			fmt_data->flag |= FLAG_ZEROS;
		if (**format == '-')
			fmt_data->flag |= FLAG_LEFT;
		(*format)++;
	}
}

void parse_width(const char **format, t_fmt *fmt_data, va_list ap)
{
	// 引数で渡された値をwidthとして使用する
	if (**format == '*')
	{
		int width = va_arg(ap, int);
		if (width < 0)
		{
			fmt_data->flag |= FLAG_LEFT;
			width = -width;
		}
		fmt_data->width = (unsigned int) width;
		(*format)++;
	}
	else if (ft_isdigit(**format))
	{
		int width = ft_atoi(*format);
		fmt_data->width = (unsigned int) width;
		(*format) += num_len(*format);
	}
}

void parse_precision(const char **format, t_fmt *fmt_data, va_list ap)
{
	if (**format == '.')
	{
		(*format)++;
		if (**format == '*')
		{
			long long precision = va_arg(ap, int);
			if (precision >= 0)
				fmt_data->precision = precision;
			(*format)++;
		}
		// 負の数が指定された場合は精度の指定は無し
		else if (**format == '-')
		{
			(*format)++;
			(*format) += num_len(*format);
		}
		// 数字が入力されていた場合
		else
		{
			fmt_data->precision = ft_atoi(*format);
			(*format) += num_len(*format);
		}
	}
}

void parse_type(const char **format, t_fmt *fmt_data)
{
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
	if (fmt_data->type == TYPE_INT || fmt_data->type == TYPE_UINT || fmt_data->type == TYPE_HEX_LOW || fmt_data->type == TYPE_HEX_UP || fmt_data->type == TYPE_POINTER)
		if (fmt_data->precision == -1)
			fmt_data->precision = 1;
	(*format)++;
}
