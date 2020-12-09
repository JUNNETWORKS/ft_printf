/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_integer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:37:07 by jtanaka           #+#    #+#             */
/*   Updated: 2020/12/10 06:57:54 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

unsigned long long get_base(enum e_type type)
{
	if (type == TYPE_HEX_LOW || type == TYPE_HEX_UP || type == TYPE_POINTER)
		return 16;
	else
		return 10;
}

int fmt_put_nbr(long long n, t_fmt *fmt_data, char **num, long long len)
{
	unsigned long long un;
	unsigned long long base;
	int write_size = 0;
	int is_minus;

	len++;
	base = get_base(fmt_data->type);
	is_minus = (!is_unsigned_type(fmt_data->type) && n < 0) ? 1 : 0;
	un = (is_unsigned_type(fmt_data->type) || n >= 0) ? n : -n;
	if (un >= base)
		len = fmt_put_nbr(un / base, fmt_data, num, len);
	else
	{
		*num = malloc(len);
		fmt_data->digit = len;
		len = 0;
	}
	if (fmt_data->type == TYPE_HEX_UP)
		(*num)[len++] = "0123456789ABCDEF"[un % base];
	else
		(*num)[len++] = "0123456789abcdef"[un % base];
	if (len == fmt_data->digit)
	{
		write_size += output_fmt_nbr(*num, fmt_data, is_minus);
		free(*num);
		return (write_size);
	}
	return (len);
}

int output_fmt_nbr(char *num, t_fmt *fmt_data, int is_minus)
{
	if (fmt_data->precision == 0 && *num == '0')
		fmt_data->digit = 0;
	int output_precision = 0; // 精度のために出力する0の数
	if (fmt_data->precision > fmt_data->digit)
		output_precision = fmt_data->precision - fmt_data->digit;
	int output_witdh = 0; // widthを満たすために埋めるスペースの数
	if (fmt_data->width > (output_precision + is_minus + fmt_data->digit))
		output_witdh = fmt_data->width - (output_precision + is_minus + fmt_data->digit);
	if (fmt_data->flag & FLAG_ZEROS)
	{
		output_precision += output_witdh;
		output_witdh = 0;
	}
	if (fmt_data->flag & FLAG_LEFT)
	{
		if (is_minus)
		  write(1, "-", 1);
		put_c_n_times('0', output_precision);
		write(1, num, fmt_data->digit);
		put_c_n_times(' ', output_witdh);
	}
	else
	{
		put_c_n_times(' ', output_witdh);
		if (is_minus)
		  write(1, "-", 1);
		put_c_n_times('0', output_precision);
		write(1, num, fmt_data->digit);
	}
	// printf("precision: %d, width: %d, digit: %llu", output_precision,
	// output_witdh, fmt_data->digit); fflush(stdout);
	return (output_witdh + output_precision + is_minus + fmt_data->digit); // write_size
}
