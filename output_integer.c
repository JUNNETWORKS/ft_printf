/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_integer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:37:07 by jtanaka           #+#    #+#             */
/*   Updated: 2020/12/12 03:02:59 by jtanaka          ###   ########.fr       */
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

int write_integer(t_fmt *fmt_data, long long n)
{
	char *num;
	int write_size;

	fmt_itoa(n, fmt_data, &num, 0);
	if (num == NULL)
		return (0);
	// TODO: 出力関数は関数ポインタで分岐するようにする.
	printf("num: %s\n", num);
	write_size = output_fmt_nbr(num, fmt_data, n < 0 ? 1 : 0);
	printf("\nwrite_size: %d\n", write_size);
	free(num);
	return (write_size);
}
	

// 関数ポインタを渡してコールバック関数のようにするか?
int fmt_itoa(long long n, t_fmt *fmt_data, char **num, long long len)
{
	unsigned long long un;
	unsigned long long base;

	len++;
	base = get_base(fmt_data->type);
	printf("\nn: %lld\n", n);
	un = (is_unsigned_type(fmt_data->type) || n >= 0) ? n : -n;
	printf("\nun: %llu\n", un);
	if (un >= base)
		len = fmt_itoa(un / base, fmt_data, num, len);
	else
	{
		if (!(*num = malloc(len + 1)))
			return -1;
		(*num)[len] = '\0';
		fmt_data->digit = len;
		len = 0;
	}
	if (fmt_data->type == TYPE_HEX_UP)
		(*num)[len++] = "0123456789ABCDEF"[un % base];
	else
		(*num)[len++] = "0123456789abcdef"[un % base];
	return (len);
}

int output_fmt_nbr(char *num, t_fmt *fmt_data, int is_minus)
{
	int output_precision;
	int output_witdh;
	int write_size;
	output_precision = 0; // 精度のために出力する0の数
	output_witdh = 0; // widthを満たすために埋めるスペースの数
	write_size = 0;

	if (fmt_data->precision == 0 && *num == '0')
		fmt_data->digit = 0;
	if (fmt_data->precision > fmt_data->digit)
		output_precision = fmt_data->precision - fmt_data->digit;
	if (fmt_data->width > (output_precision + is_minus + fmt_data->digit))
		output_witdh = fmt_data->width - (output_precision + is_minus + fmt_data->digit);
	if (fmt_data->flag & FLAG_ZEROS && fmt_data->precision <= 1)
	{
		output_precision += output_witdh;
		output_witdh = 0;
	}
	if (fmt_data->flag & FLAG_LEFT)
	{
		if (is_minus)
		  write_size += write(1, "-", 1);
		write_size += put_c_n_times('0', output_precision);
		if (fmt_data->type == TYPE_POINTER)
			write_size += write(1, "0x", 2);
		write_size += write(1, num, fmt_data->digit);
		write_size += put_c_n_times(' ', output_witdh);
	}
	else
	{
		write_size += put_c_n_times(' ', output_witdh);
		if (is_minus)
		write_size += write(1, "-", 1);
		if (fmt_data->type == TYPE_POINTER)
			write_size += write(1, "0x", 2);
		write_size += put_c_n_times('0', output_precision);
		write_size += write(1, num, fmt_data->digit);
	}
	// printf("precision: %d, width: %d, digit: %llu", output_precision,
	// output_witdh, fmt_data->digit); fflush(stdout);
	return (write_size); // write_size
}
