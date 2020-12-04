# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/07 22:12:52 by jtanaka           #+#    #+#              #
#    Updated: 2020/12/04 23:42:38 by jtanaka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_printf.c \
	   ft_printf_utils.c \
	   output_char_string.c \
	   output_fmt.c \
	   output_integer.c \
	   output_octal_hex.c \
	   parsers.c \
	   put_fmt.c
CFLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): ${OBJS}
	$(MAKE) -C ./libft
	cp libft/libft.a $(NAME)
	ar rcs $(NAME) $(OBJS)

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re 
