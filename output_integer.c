/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_integer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:37:07 by jtanaka           #+#    #+#             */
/*   Updated: 2020/12/16 08:40:33 by jtanaka          ###   ########.fr       */
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

int					write_integer(t_fmt *fmt_data, long long n)
{
	char		*num;
	int			write_size;
	int			prefix_size;

	prefix_size = 0;
	fmt_itoa(n, fmt_data, &num, 0);
	if (num == NULL)
		return (0);
	if (n < 0 && !is_unsigned_type(fmt_data->type))
		prefix_size += ++(fmt_data->is_minus);
	if (fmt_data->type == TYPE_POINTER)
		prefix_size += 2;
	write_size = output_fmt_nbr(num, fmt_data, prefix_size);
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

int					output_fmt_nbr(char *num, t_fmt *fmt_data, int prefix_size)
{
	int		zeros;
	int		spaces;

	zeros = 0;
	spaces = 0;
	if (fmt_data->precision == 0 && *num == '0')
		fmt_data->digit = 0;
	if (fmt_data->precision > fmt_data->digit)
		zeros = fmt_data->precision - fmt_data->digit;
	if (fmt_data->width > (zeros + prefix_size + fmt_data->digit))
		spaces = fmt_data->width - (zeros + prefix_size + fmt_data->digit);
	if (fmt_data->flag & FLAG_ZEROS && fmt_data->precision <= 1)
	{
		zeros += spaces;
		spaces = 0;
	}
	return (write_fmt_nbr(num, fmt_data, spaces, zeros));
}

int					write_fmt_nbr(char *num, t_fmt *fmt_data, int spaces, int zeros)
{
	int		write_size;

	write_size = 0;
	if (!(fmt_data->flag & FLAG_LEFT))
		write_size += put_c_n_times(' ', spaces);
	write_size += write(1, "-", fmt_data->is_minus);
	write_size += write(1, "0x", fmt_data->type == TYPE_POINTER ? 2 : 0);
	write_size += put_c_n_times('0', zeros);
	write_size += write(1, num, fmt_data->digit);
	if (fmt_data->flag & FLAG_LEFT)
		write_size += put_c_n_times(' ', spaces);
	return (write_size);
}

