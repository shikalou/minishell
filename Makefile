# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 16:12:42 by ldinaut           #+#    #+#              #
#    Updated: 2022/08/05 15:56:41 by ldinaut          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

SRCS_FILES	=	main.c utils_parsing.c sdf.c ft_free.c cd.c shlvl.c \
			init_struct_lst.c parsing.c execution.c exec_utils.c \
			extended_parsing.c extended_parse_utils.c strtrim_aug.c \
			builtins.c exec_multi.c redirection.c echo.c lst_utils_cmd.c \
			export.c signals.c export_parsing.c exit.c export_split.c \
			heredocs.c export_tools.c export_print.c unset.c expand_cases.c \
			lst_utils_env.c sdf_tools.c export_updt_tools.c parsing_features.c \
			export_pars_tools.c exec_cupboard.c export_errors.c \
			init_struct_utils.c

SRCS		=	$(addprefix srcs/, $(SRCS_FILES))

CC			=	gcc

LIB			=	-lreadline -Llibft -lft

CFLAGS		=	-Wall -Wextra -Werror -I./includes #-g3

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
