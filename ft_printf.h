/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 21:55:18 by jtanaka           #+#    #+#             */
/*   Updated: 2020/12/10 08:52:37 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H

#include "libft/libft.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

enum e_flag
{
	FLAG_NONE = 0b00000,
	FLAG_LEFT = 0b00001, // %- フィールドの左寄せ Mandatory
	FLAG_SIGN = 0b00010, // %+ 常に符号を付ける
	FLAG_SPACE = 0b00100, // %  数値が正または 0 の場合は符号の代わりに空白を出力
	FLAG_PREFIX = 0b01000, // %# 代替形式。基数を表すプレフィックスの出力等
	FLAG_ZEROS = 0b10000 // %0 出力文字数が最小フィールド幅未満の場合は'0'を出力 Mandatory
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

enum e_width_opt
{
	WIDTH_OPT_NONE = 0, // 特に特別なwidthオプションはない.
	WIDTH_OPT_ARG = 1,  // 引数で渡された値をwidthとして使用する
	WIDTH_OPT_PREPEND_ZEROS = 2, // (数字)先頭に0が付いていたら. 余白を0で埋める.
};

typedef struct s_fmt
{
	enum e_flag flag;
	enum e_width_opt width_opt;
	long long width;
	long long precision;
	enum e_type type;
	long long digit; // 数字の桁数
} t_fmt;

// t_fmt
t_fmt *new_t_fmt();
bool is_unsigned_type(enum e_type type);

// parsers
void parse_flag(const char **format, t_fmt *fmt_data);
void parse_width(const char **format, t_fmt *fmt_data, va_list ap);
void parse_precision(const char **format, t_fmt *fmt_data, va_list ap);
void parse_type(const char **format, t_fmt *fmt_data);

// utils
void put_c_n_times(char c, size_t n);

// printf本体と出力系と変換系
int ft_printf(const char *format, ...);
int output_fmt(t_fmt *fmt_struct, va_list ap);
int output_fmt_nbr(char *num, t_fmt *fmt_data, int is_minus);
int fmt_put_nbr(long long n, t_fmt *fmt_data, char **num, long long len);
int write_char(va_list ap);
int write_string(t_fmt *fmt_data, va_list ap);
int write_percent(t_fmt *fmt_data);
int write_fmt_data(t_fmt *fmt_data, va_list ap);
int parse_and_write(va_list ap, const char **format);

#endif
