# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 16:12:42 by ldinaut           #+#    #+#              #
#    Updated: 2022/07/15 21:54:39 by mcouppe          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

SRCS_FILES	=	main.c utils_parsing.c split_du_futur.c ft_free.c cd.c \
			init_struct_lst.c parsing.c execution.c exec_utils.c \
			extended_parsing.c extended_parse_utils.c strtrim_aug.c \
			builtins.c exec_multi.c redirection.c echo.c lst_utils_cmd.c \
			export.c signals.c parsing_export.c exit.c split_export.c \
			heredocs.c export_tools.c export_print.c unset.c expand_cases.c \
			lst_utils_env.c sdf_tools.c

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
