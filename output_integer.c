/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_integer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:37:07 by jtanaka           #+#    #+#             */
/*   Updated: 2020/12/15 08:31:47 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

unsigned long long	get_base(enum e_type type)
{
	if (type == TYPE_HEX_LOW || type == TYPE_HEX_UP || type == TYPE_POINTER)
		return (16);
	else
		return (10);
}

/*
int					wirte_prefix(t_fmt *fmt_data, long long n)
{
	int		write_size;
	int		tmp;
	int		zeros; // 精度のために出力する0の数
	int		prefix_count;   // 出力する数字以外の文字数

	zeros = (fmt_data->precision > fmt_data->digit) ? fmt_data->precision > fmt_data->digit : 0;
	prefix_count = 0;
	if (!is_unsigned_type(fmt_data->type) && n < 0)
		prefix_count += 1;
	if (fmt_data->type == TYPE_POINTER)
	    prefix_count += 2;
	write_size = 0;
	if (!is_unsigned_type(fmt_data->type) && n < 0)
		write_size += write(1, "-", 1);
	if ((tmp = fmt_data->precision - fmt_data->digit) > 0)
		write_size += put_c_n_times('0', tmp);
}
*/

int					write_integer(t_fmt *fmt_data, long long n)
{
	char	*num;
	int		write_size;

	fmt_itoa(n, fmt_data, &num, 0);
	if (num == NULL)
		return (0);
	// prefixは別の関数で行う
	write_size = output_fmt_nbr(num, fmt_data,
						(n < 0 && !is_unsigned_type(fmt_data->type)) ? 1 : 0);
	// write(1, num, ft_strlen(num));
	free(num);
	return (write_size);
}

int					fmt_itoa(long long n, t_fmt *fmt_data,
								char **num, long long len)
{
	unsigned long long	un;
	unsigned long long	base;

	len++;
	base = get_base(fmt_data->type);
	un = (is_unsigned_type(fmt_data->type) || n >= 0) ? n : -n;
	if (un >= base)
		len = fmt_itoa(un / base, fmt_data, num, len);
	else
	{
		if (!(*num = malloc(len + 1)))
			return (-1);
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

int					output_fmt_nbr(char *num, t_fmt *fmt_data, int is_minus)
{
	int		output_precision;
	int		output_width;
	int		write_size;
	int		is_pointer;

	output_precision = 0;
	output_width = 0;
	write_size = 0;
	is_pointer = fmt_data->type == TYPE_POINTER ? 2 : 0;
	if (fmt_data->precision == 0 && *num == '0')
		fmt_data->digit = 0;
	if (fmt_data->precision > fmt_data->digit)
		output_precision = fmt_data->precision - fmt_data->digit;
	if (fmt_data->width >
		(output_precision + is_minus + is_pointer + fmt_data->digit))
		output_width = fmt_data->width -
			(output_precision + is_minus + is_pointer + fmt_data->digit);
	if (fmt_data->flag & FLAG_ZEROS && fmt_data->precision <= 1)
	{
		output_precision += output_width;
		output_width = 0;
	}
	if (fmt_data->flag & FLAG_LEFT)
	{
		if (is_minus)
			write_size += write(1, "-", 1);
		if (is_pointer)
			write_size += write(1, "0x", 2);
		write_size += put_c_n_times('0', output_precision);
		write_size += write(1, num, fmt_data->digit);
		write_size += put_c_n_times(' ', output_width);
	}
	else
	{
		write_size += put_c_n_times(' ', output_width);
		if (is_minus)
			write_size += write(1, "-", 1);
		if (is_pointer)
			write_size += write(1, "0x", 2);
		write_size += put_c_n_times('0', output_precision);
		write_size += write(1, num, fmt_data->digit);
	}
	return (write_size);
}
