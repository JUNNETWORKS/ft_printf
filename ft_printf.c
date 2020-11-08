/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 22:03:47 by jtanaka           #+#    #+#             */
/*   Updated: 2020/11/09 01:08:13 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

// *formatは%の次の位置にポインタがある状態で渡される
void parse_percent(const char *format, va_list ap)
{
	t_fmt *fmt_struct;
	/* フラグの解析 */
	/* 最小フィールド幅 */
	if (ft_ispositive((char)*format))
		fmt_struct->width = ft_atoi(format);
	else if (*format == '*')
	{
		fmt_struct->width = va_arg(ap, size_t);
		(format)++;
	}

	/* 精度 */
	if (*format == '.')
	{
		if (ft_ispositive(*format))
			fmt_struct->precision = ft_atoi(format);
		else if (*format == '*')
			fmt_struct->precision = va_arg(ap, size_t);
		else
			fmt_struct->precision = 0;
		(format)++;
	}
	
	
	/* 長さ修飾子 */
	
	/* 変換指定子 ('%'もここで処理する) */

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
			parse_percent(++format, ap);
		else
		write(1, format, 1);
		format++;
	}
	va_end(ap);
}

