# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/08 16:42:54 by ldinaut           #+#    #+#              #
#    Updated: 2022/03/04 18:08:35 by ldinaut          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libftprintf.a

SRCS	=	ft_printf.c\
		ft_putc.c\
		ft_putd.c\
		ft_putnbrhexa_fd.c\
		ft_putnbr_p.c\
		ft_puts.c\
		ft_putunbr_fd.c\
		ft_countnb.c\
		ft_countnb_hex.c\
		ft_countunb.c \
		print.c

CC	=	clang

CFLAGS	=	-Wall -Wextra -Werror

OBJS	=	$(SRCS:.c=.o)

$(NAME)	:	${OBJS}
			ar rcs $(NAME) $(OBJS)

all	:	$(NAME)

.c.o	:
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

clean	:
	rm -rf $(OBJS)

fclean	:	clean
	rm -rf $(NAME)

re	:	fclean all

.PHONY: all clean fclean re
