/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 01:03:47 by jtanaka           #+#    #+#             */
/*   Updated: 2020/12/03 14:15:05 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

int parse_flag(const char *format, t_fmt **fmt_struct, va_list ap)
{
	size_t read_size;
	(*fmt_struct)->flag = 0;
	// 0埋め
	while (*format == '0')
	{
		(*fmt_struct)->flag |= PREPEND_ZEROS;
		read_size++;
	}
	// 左揃え
	while (*format == '-')
	{
		(*fmt_struct)->flag |= LEFT_ALIGNED;
		read_size++;
	}
	// 0埋め
	while (*format == '0')
	{
		(*fmt_struct)->flag |= PREPEND_ZEROS;
		read_size++;
	}
	return (read_size);
}

int parse_width(const char *format, t_fmt **fmt_struct, va_list ap)
{
	(*fmt_struct)->width = -1;
	if (*format == '*')
	{
		(*fmt_struct)->width = va_arg(ap, size_t);
		return (1);
	}
	if (ft_ispositive((char)*format))
	{
		(*fmt_struct)->width = ft_atoi(format);
		return (num_len(format));
	}
	return (0);
}

int parse_precision(const char *format, t_fmt **fmt_struct, va_list ap)
{
	size_t read_size;
	read_size = 0;
	(*fmt_struct)->precision = -1;
	if (*format == '.')
	{
		read_size++;
		if (*format == '*')
		{
			(*fmt_struct)->precision = va_arg(ap, size_t);
			read_size++;
		}
		else if (ft_ispositive(*format))
		{
			(*fmt_struct)->precision = ft_atoi(format);
			read_size += num_len(format);
		}
		else
			(*fmt_struct)->precision = 0;
	}
	return (read_size);
}

int parse_type(const char *format, t_fmt **fmt_struct)
{
	(*fmt_struct)->type = NONE_TYPE;
	if (*format == 'd' || *format == 'i')
		(*fmt_struct)->type = INT;
	else if (*format == 'o')
		(*fmt_struct)->type = OCTAL;
	else if (*format == 'u')
		(*fmt_struct)->type = UINT;
	else if (*format == 'x')
		(*fmt_struct)->type = HEX_LOW;
	else if (*format == 'X')
		(*fmt_struct)->type = HEX_UP;
	else if (*format == 'c')
		(*fmt_struct)->type = CHAR;
	else if (*format == 's')
		(*fmt_struct)->type = STRING;
	else if (*format == 'p')
		(*fmt_struct)->type = POINTER;
	else if (*format == '%')
		(*fmt_struct)->type = PERCENT;
	return (0);
}
