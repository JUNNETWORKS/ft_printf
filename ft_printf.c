/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 22:03:47 by jtanaka           #+#    #+#             */
/*   Updated: 2020/11/08 23:14:49 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// *formatは%の次の位置にポインタがある状態で渡される
void parse_percent(const char *format)
{
	// フラグの解析
	// 最小フィールド幅
	// 精度
	// 長さ修飾子
	// 変換指定子 ('%'もここで処理する)
}

int ft_printf(const char *format, ...)
{
	va_list ap;  // 可変長引数の情報を保持している型であるva_listの変数を宣言
	va_start(ap, format);  // 第二引数には可変長引数の数を渡す

	// '%'が出るまではそのまま先頭から読み込んで出力する. '%'が出現した先を解析し, 構造体として保持する.
	while (*format)
	{
		if (*format == '%')
			parse_percent(++format);
		else
		{
		write(1, *format, 1);
		}
		format++;
	}
	va_end(ap);
}

