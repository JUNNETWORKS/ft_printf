/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_fmt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 01:32:20 by jtanaka           #+#    #+#             */
/*   Updated: 2020/12/02 14:26:57 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

/* ゼロ埋めや空白埋めはどのtypeでも使うのでutilsに置く */


int write_fmt(t_fmt *fmt_struct)
{
	int write_size;
	write_size = 0;
	// typeごとに処理を分ける
	if (fmt_struct->type == INT)
		write_size += output_int(fmt_struct);
	else if(fmt_struct->type == UINT)
	else if(fmt_struct->type == OCTAL)
	else if(fmt_struct->type == HEX_LOW)
	else if(fmt_struct->type == HEX_UP)
	else if(fmt_struct->type == CHAR)
	else if(fmt_struct->type == STRING)
	else if(fmt_struct->type == POINTER)
	else
		write(1, "%", 1);
}
