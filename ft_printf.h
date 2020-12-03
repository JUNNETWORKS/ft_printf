/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 21:55:18 by jtanaka           #+#    #+#             */
/*   Updated: 2020/12/03 00:21:18 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

enum e_flag {
	FLAG_NONE		= 0b00000,
	LEFT_ALIGNED	= 0b00001,  // %- フィールドの左寄せ Mandatory
	PREPEND_SIGN	= 0b00010,  // %+ 常に符号を付ける
	PREPEND_SPACE	= 0b00100,  // %  数値が正または 0 の場合は符号の代わりに空白を出力
	PREPEND_PREFIX	= 0b01000,  // %# 代替形式。基数を表すプレフィックスの出力等
	PREPEND_ZEROS	= 0b10000	// %0 出力文字数が最小フィールド幅未満の場合は'0'を出力 Mandatory
};

enum e_length {
	LENGTH_NONE,
	LEN_HH,
	LEN_H,
	LEN_L,
	LEN_LL,
	LEN_l,
	LEN_Z,
	LEN_J,
	LEN_T
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

enum e_width_opt {
	WIDTH_OPT_NONE, 			// 特に特別なwidthオプションはない.
	WIDTH_OPT_ARG, 				// 引数で渡された値をwidthとして使用する
	WIDTH_OPT_PREPEND_ZEROS,	// (数字)先頭に0が付いていたら. 余白を0で埋める.
};


typedef struct s_fmt{
  enum e_flag flag;
  enum e_width_opt width_opt;
  unsigned int width;
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
void output_int(t_fmt *fmt_struct);
void output_uint(t_fmt *fmt_struct);
void output_octal(t_fmt *fmt_struct);
void output_hex_low(t_fmt *fmt_struct);
void output_hex_up(t_fmt *fmt_struct);
void output_char(t_fmt *fmt_struct);
void output_string(t_fmt *fmt_struct);
void output_POINTER(t_fmt *fmt_struct);
void output_fmt(t_fmt *fmt_struct);
int ft_printf(const char *format, ...);

#endif
