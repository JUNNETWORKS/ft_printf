/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 22:03:47 by jtanaka           #+#    #+#             */
/*   Updated: 2020/11/10 01:13:12 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

// *formatは%の次の位置にポインタがある状態で渡される
void parse(const char *format, va_list ap)
{
	t_fmt *fmt_struct;
	/* フラグの解析 */
	format += parse_flag(format, &fmt_struct, ap);
	/* 最小フィールド幅 */
	format += parse_width(format, &fmt_struct, ap);
	/* 精度 */
	format += parse_precision(format, &fmt_struct, ap);
	/* 長さ修飾子 */
	format += parse_length(format, &fmt_struct);
	/* 変換指定子 ('%'もここで処理する) */
	format += parse_type(format, &fmt_struct);
	/* 出力 */
}

int ft_printf(const char *format, ...)
{
	va_list ap;  // 可変長引数の情報を保持している型であるva_listの変数を宣言
	va_start(ap, format);  // 第二引数には可変長引数の数を渡す

	// '%'が出るまではそのまま先頭から読み込んで出力する. '%'が出現した先を解析し, 構造体として保持する.
	while (*format)
	{
		if (*format == '%')
			parse(++format, ap);
		else
		write(1, format, 1);
		format++;
	}
	va_end(ap);
}

