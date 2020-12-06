/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_integer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 02:37:07 by jtanaka           #+#    #+#             */
/*   Updated: 2020/12/06 20:12:37 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

unsigned long long get_base(enum e_type type)
{
  if (type == TYPE_HEX_LOW || type == TYPE_HEX_UP || type == TYPE_POINTER)
	return 16;
  else
	return 10;
}

int fmt_strlen(long long n, t_fmt *fmt_data)
{
  int len;

  len = 0;
	while (n){
	  n /= get_base(fmt_data->type);
	  len++;
	}
  return len;
}

bool is_unsigned_type(enum e_type type)
{
  return (type == TYPE_UINT || type == TYPE_HEX_UP || type == TYPE_HEX_LOW || type == TYPE_POINTER);
}


int fmt_put_nbr(long long n, t_fmt *fmt_data, char **num, int len)
{
	unsigned long long un;
	unsigned long long base;

	len++;
	base = get_base(fmt_data->type);
	un = (is_unsigned_type(fmt_data->type) || n >= 0) ? n : -n;
	if (un >= base)
	  len = fmt_put_nbr(un / base, fmt_data, num, len);
	if (un < base)
	{
	  *num = malloc(len + 1);
	  fmt_data->digit = len;
	  len = 0;
	}
	if (fmt_data->type == TYPE_HEX_UP)
		(*num)[len++] = "0123456789ABCDEF"[un % base];
	else
		(*num)[len++] = "0123456789abcdef"[un % base];
	if (len == fmt_data->digit)
	{
	  (*num)[len] = '\0';
	  write(1, *num, len);
	  free(*num);
	}
	return (len);

}
