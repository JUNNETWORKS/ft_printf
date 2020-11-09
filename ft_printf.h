/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 21:55:18 by jtanaka           #+#    #+#             */
/*   Updated: 2020/11/10 01:20:01 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

enum e_flag {
	NONE_FLAG		= 0b00000,
	LEFT_ALIGNED	= 0b00001,  // %- フィールドの左寄せ
	PREPEND_SIGN	= 0b00010,  // %+ 常に符号を付ける
	PREPEND_SPACE	= 0b00100,  // %  数値が正または 0 の場合は符号の代わりに空白を出力
	PREPEND_PREFIX	= 0b01000,  // %# 代替形式。基数を表すプレフィックスの出力等
	PREPEND_ZEROS	= 0b10000	// %0 出力文字数が最小フィールド幅未満の場合は'0'を出力
};

enum e_length {
	NONE_LENGTH,
	hh,
	h,
	l,
	ll,
	L,
	z,
	j,
	t
};

enum e_type {
	NONE_TYPE,
	PERCENT,
	INTGER,
	UNS_INT,
	CHAR,
	STRING,
	POINTER,
	OCTAL,
	HEX_LOW,
	HEX_UP,
};

typedef struct s_fmt{
  e_flag flag;
  ssize_t width;
  ssize_t precision;
  e_length length;
  e_type type;
} t_fmt;

int ft_ispositive(int c);
int parse_flag(const char *format, t_fmt **fmt_struct, va_list ap);
int parse_width(const char *format, t_fmt **fmt_struct, va_list ap);
int parse_precision(const char *format, t_fmt **fmt_struct, va_list ap);
int parse_length(const char *format, t_fmt **fmt_struct);
int parse_type(const char *format, t_fmt **fmt_struct);
int ft_printf(const char *format, ...);

#endif
