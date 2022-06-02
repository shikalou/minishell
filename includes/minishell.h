/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:47:27 by ldinaut           #+#    #+#             */
/*   Updated: 2022/06/02 13:23:42 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_env_lst
{
	int					index;
	char				*line;
	struct s_env_lst	*next;
}	t_env_lst;

typedef struct s_cmd_lst
{
	int					index;
	char				*command;
	struct s_cmd_lst	*next;
}	t_cmd_lst;

typedef struct s_big_struct
{
	char		**input;
	char		*absolut_path;
	t_env_lst	*env_lst;
	t_cmd_lst	*cmd_lst;
}	t_big_struct;

t_big_struct	*ft_init_big_struct(char **envp);

t_cmd_lst		*ft_init_cmd_lst(char **input);
t_cmd_lst		*ft_lstnew_cmd(int i, char *cmd);
void			ft_lstadd_back_cmd(t_cmd_lst **alst, t_cmd_lst *new);

t_env_lst		*ft_init_env_lst(char **envp);
t_env_lst		*ft_lstnew_env(int i, char *env_line);
void			ft_lstadd_back_env(t_env_lst **alst, t_env_lst *new);

char			**ft_split_du_futur(char const *s1, char c);

/* parsing */
char			*add_space(char *cmd, int index);
char			*add_space_hereapp(char *cmd, int index);
char			*check_spe_char(char *cmd);

int				charisalphaorspace(char c);
int				charisalpha(char c);
int				charisalpha_aug(char *cmd, int index, int end);
int				ft_parsing(char *cmd, t_big_struct *big_struct);
int				ft_split_quotes(const char *s1, int i);

void			shellmini(t_big_struct *big_struct);
void			ft_exec(t_big_struct *big_struct);

#endif
