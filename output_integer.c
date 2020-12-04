/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_integer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:37:07 by jtanaka           #+#    #+#             */
/*   Updated: 2020/12/03 14:51:23 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

ret = put_nbr(n, flag, &num, 0);

int            put_nbr(long long n, char *flag, char **num, int len)
{
    unsigned long long    un;

    len++;
    un = (flag[UNSIGNED] || n >= 0) ? n : -n;
    if (un >= (unsigned long long)flag[BASE])
        len = put_nbr(un / flag[BASE], flag, num, len);
    if (un < (unsigned long long)flag[BASE])
    {
        *num = malloc(len + 1);
        flag[DIGIT] = len;
        len = 0;
    }
    if (flag['X'])
        (*num)[len++] = "0123456789ABCDEF"[un % flag[BASE]];
    else
        (*num)[len++] = "0123456789abcdef"[un % flag[BASE]];
    if (len == (int)flag[DIGIT])
    {
        (*num)[len] = '\0';
        write(1, *num, len);
        free(*num);
    }
    return (len);
}

int put_nbr(long long n, t_fmt *fmt_data, char **num, int len);

int output_int(t_fmt *fmt_data, va_list ap){
	long long n;

	n = va_arg(ap, long long);
	return (put_fmt_nbr(n, fmt_data, NULL, 0));
}

int output_uint(t_fmt *fmt_data, va_list ap){

}
