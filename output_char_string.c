/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_char_string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:38:46 by jtanaka           #+#    #+#             */
/*   Updated: 2020/12/03 14:31:01 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

int write_char(t_fmt *fmt_struct, va_list ap){
	unsigned char c;

	c = (unsigned char)va_arg(ap, int);
	return (write(1, &c, 1));
}

int write_string(t_fmt *fmt_struct, va_list ap){
	const char *str;

	str = (const char*)va_arg(ap, const char*);
	return (write(1, str, ft_strlen(str)));
}
