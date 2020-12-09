/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_percent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 08:46:42 by jtanaka           #+#    #+#             */
/*   Updated: 2020/12/10 08:52:07 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int write_percent(t_fmt *fmt_data)
{
	int output_width;

	output_width = 0;
	if (fmt_data->width > 0)
		output_width = fmt_data->width - 1;
	if (fmt_data->flag == FLAG_LEFT)
	{
	write(1, "%", 1);
	put_c_n_times(' ', output_width);
	}
	else
	{
	put_c_n_times(' ', output_width);
	write(1, "%", 1);
	}
	return (output_width + 1);
}
