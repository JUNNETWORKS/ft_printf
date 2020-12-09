/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_char_string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:38:46 by jtanaka           #+#    #+#             */
/*   Updated: 2020/12/10 02:43:56 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

int write_char(va_list ap)
{
	unsigned char c;

	c = (unsigned char) va_arg(ap, int);
	return (write(1, &c, 1));
}

int write_string(t_fmt *fmt_data, va_list ap)
{
	const char *str;
	size_t output_str_len;
	size_t output_width; // 最少フィールド幅のために出力する空白の数

	str = (const char *) va_arg(ap, const char *);
	output_str_len = ft_strlen(str);
	output_width = 0;
	if (fmt_data->precision > 0 && output_str_len > fmt_data->precision)
		output_str_len = fmt_data->precision;
	if (fmt_data->width > output_str_len)
		output_width = fmt_data->width - output_str_len;

	if (fmt_data->flag & LEFT_ALIGNED)
	{
		write(1, str, output_str_len);
		put_c_n_times(' ', output_width);
	}
	else
	{
		put_c_n_times(' ', output_width);
		write(1, str, output_str_len);
	}
	return (output_width + output_str_len);
}
