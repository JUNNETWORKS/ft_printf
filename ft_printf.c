/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 07:20:53 by jtanaka           #+#    #+#             */
/*   Updated: 2020/12/14 08:44:31 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

int		ft_printf(const char *format, ...)
{
	int		write_size;
	va_list	ap;

	write_size = 0;
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

int		parse_and_write(va_list ap, const char **format)
{
	int		write_size;
	t_fmt	*fmt_data;

	write_size = 0;
	fmt_data = new_t_fmt();
	parse_flag(format, fmt_data);
	parse_width(format, fmt_data, ap);
	parse_precision(format, fmt_data, ap);
	parse_type(format, fmt_data);
	// printf("\n\tflag: %d\n\twidth: %lld\n\tprecision: %lld\n\ttype: %d\n", fmt_data->flag, fmt_data->width, fmt_data->precision, fmt_data->type);
	write_size += write_fmt_data(fmt_data, ap);
	free(fmt_data);
	return (write_size);
}

int		write_fmt_data(t_fmt *fmt_data, va_list ap)
{
	long long	n;
	if (fmt_data->type == TYPE_PERCENT)
		return (write_percent(fmt_data));
	if (fmt_data->type == TYPE_CHAR)
		return (write_char(fmt_data, ap));
	else if (fmt_data->type == TYPE_STRING)
		return (write_string(fmt_data, ap));
	else if (fmt_data->type == TYPE_UINT || fmt_data->type == TYPE_HEX_LOW || fmt_data->type == TYPE_HEX_UP)
	{
		n = (unsigned int)va_arg(ap, int);
		return (write_integer(fmt_data, n));
	}
	else if (fmt_data->type == TYPE_INT)
	{
		n = va_arg(ap, int);
		return (write_integer(fmt_data, n));
	}
	else if (fmt_data->type == TYPE_POINTER)
	{
		n = va_arg(ap, long);
		return (write_integer(fmt_data, n));
	}
	return (0);
}
