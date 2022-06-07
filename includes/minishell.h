/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:47:27 by ldinaut           #+#    #+#             */
/*   Updated: 2022/06/07 20:44:39 by mcouppe          ###   ########.fr       */
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

/********************************************************/
/***********INIT AND START*******************************/
/********************************************************/
void			shellmini(t_big_struct *big_struct);

t_big_struct	*ft_init_big_struct(char **envp);

/*		--> INIT CMD_LST			*/
t_cmd_lst		*ft_init_cmd_lst(char **input);
t_cmd_lst		*ft_lstnew_cmd(int i, char *cmd);
void			ft_lstadd_back_cmd(t_cmd_lst **alst, t_cmd_lst *new);

/*		--> INIT ENV_LST			*/
t_env_lst		*ft_init_env_lst(char **envp);
t_env_lst		*ft_lstnew_env(int i, char *env_line);
void			ft_lstadd_back_env(t_env_lst **alst, t_env_lst *new);

/********************************************************/
/*************PARSING************************************/
/********************************************************/
int				ft_parsing(char *cmd, t_big_struct *big_struct);

/*		--> PARSING QUOTES			*/
void			parsing_quotes(t_big_struct *big_struct);

char			*extended_dollar(char *cmd, t_big_struct *big_struct);
char			*ft_get_env_var(t_big_struct *big_struct, char *cmd, int index);
char			*get_env_lst(char *cmd, int i, int j);
char			*strtrim_aug(char *cmd);
int				ft_len_dollar(char *cmd, int i);
int				ft_memchr_aug(char *s, int i, char c);
int				strtrim_size(char *cmd);

/*		--> UTILS PARSING			*/
char			**ft_split_du_futur(char const *s1, char c);
char			*add_space(char *cmd, int index);
char			*add_space_hereapp(char *cmd, int index);
char			*check_spe_char(char *cmd);
char			*strtrim_aug(char *cmd);
int				check_char(char c);
int				check_str(char *cmd, int index, int end);
int				check_char_basic(char c);
int				ft_split_quotes(const char *s1, int i);

/********************************************************/
/*************EXECUTION**********************************/
/********************************************************/
void			ft_exec(t_big_struct *big_struct);

/*		--> UTILS ALL				*/
char			*ft_strnstr_exec(char *s1, char *s2, size_t n);

/*		--> BUILTIN				*/
void			ft_pwd(t_big_struct *big_struct);

/*		--> HEREDOC, APPEND & REDIREC		*/
void			ft_heredoc(t_big_struct *big_struct);
/*			->utils				*/
char			*ft_strnstr_hd(char *s1, char *s2, size_t n, size_t i);
int				get_next_heredoc(char *s1, char *s2, int i);

/********************************************************/
/********************************************************/
#endif
