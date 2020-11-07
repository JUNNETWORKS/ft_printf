# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtanaka <jtanaka@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/07 22:12:52 by jtanaka           #+#    #+#              #
#    Updated: 2020/11/08 02:07:46 by jtanaka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_printf.c
CFLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a
SRCS = ft_printf.c
OBJS = $(SRCS:.c=.c)

all: $(NAME)

$(NAME): ${OBJS}
	$(MAKE) -C ./libft
	cp libft/libft.a $(NAME)
	ar rcs $(NAME) $(OBJS)

clean:
	${RM} ${OBJS} ${B_OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re 
