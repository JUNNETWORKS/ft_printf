/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 01:03:47 by jtanaka           #+#    #+#             */
/*   Updated: 2020/11/10 01:00:03 by jtanaka          ###   ########.fr       */
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
	size_t read_size;
	read_size = 0;
	(*fmt_struct)->length = NONE_LENGTH;
	if (*format == 'h')
	{
	  if (*(format+1) == 'h')
		(*fmt_struct)->length = hh;
	  else
		(*fmt_struct)->length = h;
	}
	else if (*format == 'l')
	{
	  if (*(format + 1) == 'l')
		(*fmt_struct)->length = ll;
	  else
		(*fmt_struct)->length = l;
	}
}
