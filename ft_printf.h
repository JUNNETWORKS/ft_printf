/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 21:55:18 by jtanaka           #+#    #+#             */
/*   Updated: 2020/12/14 09:19:21 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft/libft.h"
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

enum e_flag
{
	FLAG_NONE = 0b00000,
	FLAG_LEFT = 0b00001,
	FLAG_SIGN = 0b00010,
	FLAG_SPACE = 0b00100,
	FLAG_PREFIX = 0b01000,
	FLAG_ZEROS = 0b10000
};

enum e_type
{
	TYPE_NONE = 0,
	TYPE_PERCENT = 1,
	TYPE_INT = 2,
	TYPE_UINT = 3,
	TYPE_CHAR = 4,
	TYPE_STRING = 5,
	TYPE_POINTER = 6,
	TYPE_HEX_LOW = 7,
	TYPE_HEX_UP = 8,
};

typedef struct s_fmt
{
	enum e_flag	flag;
	long long	width;
	long long	precision;
	enum e_type type;
	long long	digit;
}		t_fmt;

t_fmt	*new_t_fmt();
bool	is_unsigned_type(enum e_type type);
bool	is_integer_type(enum e_type type);
void	parse_flag(const char **format, t_fmt *fmt_data);
void	parse_width(const char **format, t_fmt *fmt_data, va_list ap);
void	parse_precision(const char **format, t_fmt *fmt_data, va_list ap);
void	parse_type(const char **format, t_fmt *fmt_data);
int		put_c_n_times(char c, int n);
int		ft_printf(const char *format, ...);
int		output_fmt(t_fmt *fmt_struct, va_list ap);
int		output_fmt_nbr(char *num, t_fmt *fmt_data, int is_minus);
int		fmt_itoa(long long n, t_fmt *fmt_data, char **num, long long len);
int		write_char(t_fmt *fmt_data, va_list ap);
int		write_string(t_fmt *fmt_data, va_list ap);
int		write_integer(t_fmt *fmt_data, long long n);
int		write_percent(t_fmt *fmt_data);
int		write_fmt_data(t_fmt *fmt_data, va_list ap);
int		parse_and_write(va_list ap, const char **format);

#endif
