/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 22:03:47 by jtanaka           #+#    #+#             */
/*   Updated: 2020/12/03 14:33:32 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

// *formatは%の次の位置にポインタがある状態で渡される
// 出力した文字数を返す
int parse_and_write(const char **format, va_list ap)
{
	t_fmt *fmt_struct;
	/* フラグの解析 */
	*format += parse_flag(*format, &fmt_struct, ap);
	/* 最小フィールド幅 */
	*format += parse_width(*format, &fmt_struct, ap);
	/* 精度 */
	*format += parse_precision(*format, &fmt_struct, ap);
	/* 変換指定子 ('%'もここで処理する) */
	*format += parse_type(*format, &fmt_struct);
	/* 出力 */
	return (output_fmt(fmt_struct, ap));
}

int ft_printf(const char *format, ...)
{
	int read_size;
	va_list ap;  // 可変長引数の情報を保持している型であるva_listの変数を宣言
	va_start(ap, format);  // 第二引数には可変長引数の数を渡す

	read_size = 0;

	// '%'が出るまではそのまま先頭から読み込んで出力する. '%'が出現した先を解析し, 構造体として保持する.
	while (*format)
	{
		if (*format == '%'){
			format++;
			read_size += parse_and_write(&format, ap);
		}
		else{
			write(1, format, 1);
			read_size++;
		}
		format++;
	}
	va_end(ap);
	return (read_size);
}

