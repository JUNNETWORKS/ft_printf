/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 21:55:18 by jtanaka           #+#    #+#             */
/*   Updated: 2020/11/08 20:15:18 by jtanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

enum e_flag {
	DEFAULT			= 0b00000,
	LEFT_ALIGNED	= 0b00001,  // %- フィールドの左寄せ
	PREPEND_SIGN	= 0b00010,  // %+ 常に符号を付ける
	PREPEND_SPACE	= 0b00100,  // %  数値が正または 0 の場合は符号の代わりに空白を出力
	PREPEND_PREFIX	= 0b01000,  // %# 代替形式。基数を表すプレフィックスの出力等
	PREPEND_ZEROS	= 0b10000	// %0 出力文字数が最小フィールド幅未満の場合は'0'を出力
};

typedef struct s_fmt{
  e_flag flag;
  int width;
  int precision;
  
} t_fmt;

int ft_printf(const char *format, ...);

#endif
