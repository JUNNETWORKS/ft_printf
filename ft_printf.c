/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 22:03:47 by jtanaka           #+#    #+#             */
/*   Updated: 2020/11/10 02:22:53 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

// *formatは%の次の位置にポインタがある状態で渡される
// 返り値は進んだバイト数
size_t parse_and_write(const char *format, va_list ap)
{
	size_t read_size;
	read_size = 0;
	t_fmt *fmt_struct;
	/* フラグの解析 */
	read_size += parse_flag((format + read_size), &fmt_struct, ap);
	/* 最小フィールド幅 */
	read_size += parse_width((format + read_size), &fmt_struct, ap);
	/* 精度 */
	read_size += parse_precision((format + read_size), &fmt_struct, ap);
	/* 長さ修飾子 */
	read_size += parse_length((format + read_size), &fmt_struct);
	/* 変換指定子 ('%'もここで処理する) */
	read_size += parse_type((format + read_size), &fmt_struct);
	/* 出力 */

	return (read_size);
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

