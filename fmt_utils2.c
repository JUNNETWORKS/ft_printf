/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 11:03:50 by jtanaka           #+#    #+#             */
/*   Updated: 2020/12/16 11:08:42 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

bool	will_output_sign(t_fmt *fmt_data)
{
	return (fmt_data->is_minus ||
		(fmt_data->flag & FLAG_SIGN && !is_unsigned_type(fmt_data->type)));
}
