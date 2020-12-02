/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 22:03:47 by jtanaka           #+#    #+#             */
/*   Updated: 2020/12/02 14:18:18 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

// *formatは%の次の位置にポインタがある状態で渡される
// 返り値は進んだバイト数
size_t parse_and_write(const char *format, va_list ap)
{
	size_t output_size;
	output_size = 0;
	t_fmt *fmt_struct;
	/* フラグの解析 */
	output_size += parse_flag((format + output_size), &fmt_struct, ap);
	/* 最小フィールド幅 */
	output_size += parse_width((format + output_size), &fmt_struct, ap);
	/* 精度 */
	output_size += parse_precision((format + output_size), &fmt_struct, ap);
	/* 長さ修飾子 */
	output_size += parse_length((format + output_size), &fmt_struct);
	/* 変換指定子 ('%'もここで処理する) */
	output_size += parse_type((format + output_size), &fmt_struct);
	/* 出力 */
	output_fmt(fmt_struct);

	return (output_size);
}

int ft_printf(const char *format, ...)
{
	int output_size;
	va_list ap;  // 可変長引数の情報を保持している型であるva_listの変数を宣言
	va_start(ap, format);  // 第二引数には可変長引数の数を渡す

	output_size = 0;

	// '%'が出るまではそのまま先頭から読み込んで出力する. '%'が出現した先を解析し, 構造体として保持する.
	while (*format)
	{
		if (*format == '%')
			output_size += parse_and_write(++format, ap);
		else{
	    	write(1, format, 1);
			output_size++;
		}
		format++;
	}
	va_end(ap);
	return (output_size);
}

