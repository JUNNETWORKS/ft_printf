/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 02:27:40 by jtanaka           #+#    #+#             */
/*   Updated: 2020/12/09 02:27:55 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_fmt *new_t_fmt()
{
  t_fmt* fmt_data = malloc(sizeof(t_fmt));
  fmt_data->flag = FLAG_NONE;
  fmt_data->precision = 0;
  fmt_data->type = TYPE_NONE;
  fmt_data->width = 0;
  fmt_data->width_opt = WIDTH_OPT_NONE;
  fmt_data->digit = 0;
  return (fmt_data);
}

