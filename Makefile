# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 16:12:42 by ldinaut           #+#    #+#              #
#    Updated: 2022/06/27 15:22:29 by ldinaut          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

SRCS_FILES	=	main.c utils_parsing.c split_du_futur.c lst_utils.c \
			init_struct_lst.c parsing.c execution.c exec_utils.c \
			extended_parsing.c extended_parse_utils.c strtrim_aug.c \
			builtins.c exec_multi.c redirection.c ft_free.c echo.c cd.c \
			retry_export.c ft_split_export.c signals.c

SRCS		=	$(addprefix srcs/, $(SRCS_FILES))

CC			=	gcc

LIB			=	-lreadline -Llibft -lft

CFLAGS		=	-Wall -Wextra -Werror -g3 -I./includes

OBJS_FILES	=	$(SRCS_FILES:%.c=%.o)

OBJS		=	$(addprefix objs/, $(OBJS_FILES))

DEP			=	$(OBJS:%.o=%.d)

all		:	$(NAME)

$(NAME)	:	$(OBJS)
	make -C libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB)

clean	:
	make -C libft clean
	rm -rf $(OBJS) $(DEP)
	rm -rf objs/

fclean	:	clean
	make -C libft fclean
	rm -rf $(NAME)

re		:	fclean all

objs/%.o	: srcs/%.c includes/minishell.h
	mkdir -p objs
	$(CC) $(CFLAGS) -MMD -o $@ -c $<

.PHONY: all clean fclean re
