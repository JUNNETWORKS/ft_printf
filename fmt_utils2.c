/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 11:03:50 by jtanaka           #+#    #+#             */
/*   Updated: 2020/12/17 06:04:33 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

bool	will_output_sign(t_fmt *fmt_data)
{
	return (fmt_data->is_minus ||
		((fmt_data->flag & FLAG_SIGN || fmt_data->flag & FLAG_SPACE) &&
			!is_unsigned_type(fmt_data->type)));
}

char	*get_sign_prefix(t_fmt *fmt_data)
{
	if (fmt_data->is_minus)
		return ("-");
	else if (fmt_data->flag & FLAG_SPACE)
		return (" ");
	else if (fmt_data->flag & FLAG_SIGN)
		return ("+");
	else
		return ("");
}
