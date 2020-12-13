/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 02:27:40 by jtanaka           #+#    #+#             */
/*   Updated: 2020/12/14 08:43:36 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_fmt *new_t_fmt()
{
	t_fmt *fmt_data;
	
	fmt_data = malloc(sizeof(t_fmt));
	fmt_data->flag = FLAG_NONE;
	fmt_data->precision = -1;
	fmt_data->type = TYPE_NONE;
	fmt_data->width = 0;
	fmt_data->digit = 0;
	return (fmt_data);
}

bool is_unsigned_type(enum e_type type)
{
	return (type == TYPE_UINT || type == TYPE_HEX_UP || type == TYPE_HEX_LOW || type == TYPE_POINTER);
}
