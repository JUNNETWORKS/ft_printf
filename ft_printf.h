/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 21:55:18 by jtanaka           #+#    #+#             */
/*   Updated: 2020/12/02 14:10:02 by jtanaka          ###   ########.fr       */
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
	len_hh,
	len_h,
	len_l,
	len_ll,
	len_L,
	len_z,
	len_j,
	len_t
};

enum e_type {
	NONE_TYPE,
	PERCENT,
	INT,
	UINT,
	CHAR,
	STRING,
	POINTER,
	OCTAL,
	HEX_LOW,
	HEX_UP,
};

typedef struct s_fmt{
  enum e_flag flag;
  ssize_t width;
  ssize_t precision;
  enum e_length length;
  enum e_type type;
} t_fmt;

int ft_ispositive(int c);
int parse_flag(const char *format, t_fmt **fmt_struct, va_list ap);
int parse_width(const char *format, t_fmt **fmt_struct, va_list ap);
int parse_precision(const char *format, t_fmt **fmt_struct, va_list ap);
int parse_length(const char *format, t_fmt **fmt_struct);
int parse_type(const char *format, t_fmt **fmt_struct);
void write_int(t_fmt *fmt_struct);
void write_uint(t_fmt *fmt_struct);
void write_octal(t_fmt *fmt_struct);
void write_hex_low(t_fmt *fmt_struct);
void write_hex_up(t_fmt *fmt_struct);
void write_char(t_fmt *fmt_struct);
void write_string(t_fmt *fmt_struct);
void write_POINTER(t_fmt *fmt_struct);
void write_fmt(t_fmt *fmt_struct);
int ft_printf(const char *format, ...);

#endif
