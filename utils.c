/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 02:39:12 by jtanaka           #+#    #+#             */
/*   Updated: 2020/12/10 02:48:56 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void put_c_n_times(char c, size_t n)
{
  if (n <= 0)
	  return;
  size_t i;
  i = 0;
  while (i++ < n)
	write(1, &c, 1);
}

