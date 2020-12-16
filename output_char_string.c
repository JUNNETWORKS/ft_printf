/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_char_string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:38:46 by jtanaka           #+#    #+#             */
/*   Updated: 2020/12/16 10:08:52 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

int		write_char(t_fmt *fmt_data, va_list ap)
{
	unsigned char	c;
	int				write_size;

	write_size = 0;
	c = (unsigned char)va_arg(ap, int);
	if (fmt_data->width > 0 && !(fmt_data->flag & FLAG_LEFT))
		write_size += write_c_n_times(' ', fmt_data->width - 1);
	write_size += write(1, &c, 1);
	if (fmt_data->width > 0 && fmt_data->flag & FLAG_LEFT)
		write_size += write_c_n_times(' ', fmt_data->width - 1);
	return (write_size);
}

int		write_string(t_fmt *fmt_data, va_list ap)
{
	const char	*str;
	long long	output_str_len;
	long long	output_width;

	str = (const char *)va_arg(ap, const char *);
	str = str ? str : "(null)";
	output_str_len = ft_strlen(str);
	output_width = 0;
	if (fmt_data->precision >= 0 && output_str_len > fmt_data->precision)
		output_str_len = fmt_data->precision;
	if (fmt_data->width > output_str_len)
		output_width = fmt_data->width - output_str_len;
	if (fmt_data->flag & FLAG_LEFT)
	{
		write(1, str, output_str_len);
		write_c_n_times(' ', output_width);
	}
	else
	{
		write_c_n_times(fmt_data->flag & FLAG_ZEROS ? '0' : ' ', output_width);
		write(1, str, output_str_len);
	}
	return (output_width + output_str_len);
}
