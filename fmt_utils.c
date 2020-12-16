/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 02:27:40 by jtanaka           #+#    #+#             */
/*   Updated: 2020/12/16 10:33:33 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		initialize_t_fmt(t_fmt *fmt_data)
{
	fmt_data->flag = FLAG_NONE;
	fmt_data->precision = -1;
	fmt_data->type = TYPE_NONE;
	fmt_data->width = 0;
	fmt_data->digit = 0;
	fmt_data->is_minus = 0;
}

bool		is_unsigned_type(enum e_type type)
{
	return (type == TYPE_UINT || type == TYPE_HEX_UP ||
			type == TYPE_HEX_LOW || type == TYPE_POINTER);
}

bool		is_integer_type(enum e_type type)
{
	return (type == TYPE_INT || type == TYPE_UINT ||
			type == TYPE_HEX_LOW || type == TYPE_HEX_UP);
}

bool		will_output_base(t_fmt *fmt_data)
{
	return (fmt_data->type == TYPE_POINTER || (get_base_from_type(fmt_data->type) == 16 && fmt_data->flag & FLAG_SIGN));
}

uint64_t	get_base_from_type(enum e_type type)
{
	if (type == TYPE_HEX_LOW || type == TYPE_HEX_UP || type == TYPE_POINTER)
		return (16);
	else
		return (10);
}
