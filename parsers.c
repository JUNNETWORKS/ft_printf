/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 01:03:47 by jtanaka           #+#    #+#             */
/*   Updated: 2020/11/10 01:22:14 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

int parse_flag(const char *format, t_fmt **fmt_struct, va_list ap)
{
	size_t read_size;
	(*fmt_struct)->flag = 0;
	// 左揃え
	if (*format == '-')
	{
		(*fmt_struct)->flag |= LEFT_ALIGNED;
		read_size++;
	}
	// 0埋め
	if (*format == '0')
	{
		(*fmt_struct)->flag |= PREPEND_ZEROS;
		read_size++;
	}
	return (read_size);
}

int parse_width(const char *format, t_fmt **fmt_struct, va_list ap)
{
	(*fmt_struct)->width = -1;
	if (ft_ispositive((char)*format))
	{
		(*fmt_struct)->width = ft_atoi(format);
		return (num_len(format));
	}
	if (*format == '*')
	{
		(*fmt_struct)->width = va_arg(ap, size_t);
		return (1);
	}
}

int parse_precision(const char *format, t_fmt **fmt_struct, va_list ap)
{
	size_t read_size;
	read_size = 0;
	(*fmt_struct)->precision = -1;
	if (*format == '.')
	{
		read_size++;
		if (ft_ispositive(*format))
		{
			(*fmt_struct)->precision = ft_atoi(format);
			read_size += num_len(format);
		}
		else if (*format == '*')
		{
			(*fmt_struct)->precision = va_arg(ap, size_t);
			read_size++;
		}
		else
			(*fmt_struct)->precision = 0;
	}
	return (read_size);
}

int parse_length(const char *format, t_fmt **fmt_struct)
{
	(*fmt_struct)->length = NONE_LENGTH;
	// 2文字のLength
	if (*format == 'h' && *(format + 1) == 'h')
		(*fmt_struct)->length = hh;
	else if (*format == 'l' && *(format + 1) == 'l')
		(*fmt_struct)->length = ll;
	if ((*fmt_struct)->length != NONE_LENGTH)
		return (2);
	// 1文字のLength
	if (*format == 'h')
		(*fmt_struct)->length = h;
	else if (*format == 'l')
		(*fmt_struct)->length = l;
	else if (*format == 'L')
		(*fmt_struct)->length = L;
	else if (*format == 'z')
		(*fmt_struct)->length = z;
	else if (*format == 'j')
		(*fmt_struct)->length = j;
	else if (*format == 't')
		(*fmt_struct)->length = t;
	if ((*fmt_struct)->length != NONE_LENGTH)
		return (1);
	return (0);
}

int parse_type(const char *format, t_fmt **fmt_struct)
{
	(*fmt_struct)->type = NONE_TYPE;
	if (*format == 'd' || *format == 'i')
		(*fmt_struct)->type = INTGER;
	else if (*format == 'o')
		(*fmt_struct)->type = OCTAL;
	else if (*format == 'u')
		(*fmt_struct)->type = UNS_INT;
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
	if ((*fmt_struct)->type != NONE_LENGTH)
		return (1);
	return (0);
}
