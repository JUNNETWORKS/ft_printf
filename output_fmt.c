/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_fmt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 01:32:20 by jtanaka           #+#    #+#             */
/*   Updated: 2020/11/10 02:38:14 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

/* ゼロ埋めや空白埋めはどのtypeでも使うのでutilsに置く */

void write_char(t_fmt *fmt_struct)
void write_string(t_fmt *fmt_struct)
void write_POINTER(t_fmt *fmt_struct)

void write_fmt(t_fmt *fmt_struct)
{
	// typeごとに処理を分ける
	if (fmt_struct->type == INT)
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
