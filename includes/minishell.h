/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:47:27 by ldinaut           #+#    #+#             */
/*   Updated: 2022/07/14 15:54:39 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <limits.h>
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
	int					fd_in;
	int					fd_out;
	pid_t				pid;
	struct s_cmd_lst	*next;
}	t_cmd_lst;

typedef struct s_big_struct
{
	char		**input;
	char		**envp;
	char		**path;
	char		**spaced_cmd;
	char		**spaced_par;
	char		*absolut_path;
	char		*cmd_updated;
	char		*check_name;
	int			check_export;
	int			check_unset;
	int			env_size;
	int			pipefd[2];
	int			status;
	char		*c_status;
	char		*random_file;
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
void			ft_lstclear_cmd(t_cmd_lst *cmd_lst);
int				ft_lstsize_cmd(t_cmd_lst *lst);

/*		--> INIT ENV_LST			*/
t_env_lst		*ft_init_env_lst(char **envp);
t_env_lst		*ft_lstnew_env(int i, char *env_line);
void			ft_lstadd_back_env(t_env_lst **alst, t_env_lst *new);
void			ft_lstclear_env(t_env_lst *env_lst);
void			ft_lstdelone_env(t_env_lst **lst, void(*del)(void *));
int				ft_lstsize_env(t_env_lst *lst);

/********************************************************/
/*************PARSING************************************/
/********************************************************/
int				ft_parsing(char *cmd, t_big_struct *big_struct);

/*		--> PARSING QUOTES			*/
void			parsing_quotes(t_big_struct *big_struct);

char			*extended_dollar(char *cmd, t_big_struct *big_struct);
char			*ft_get_env_var(t_big_struct *big_struct, char *cmd, int index);
char			*get_env_lst(char *cmd, int i, int j, t_big_struct *big_struct);
char			*strtrim_aug(char *cmd);
int				ft_len_dollar(char *cmd, int i);
int				ft_memchr_aug(char *s, int i, char c);
int				strtrim_size(char *cmd);

/*		--> PARSING REDIRECTIONS	*/
void			parsing_redirection(t_big_struct *big_struct);

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
void			ft_multi_pipe(t_big_struct *big_struct);
void			first_exec(t_big_struct *big_struct, t_cmd_lst *cmd_lst);
void			middle_exec(t_big_struct *big_struct, t_cmd_lst *cmd_lst);
void			last_exec(t_big_struct *big_struct, t_cmd_lst *cmd_lst);
int				ft_simple_exec(t_big_struct *big_struct, t_cmd_lst *cmd_lst);
int				ft_check_builtin_multi(t_big_struct *big_struct, t_cmd_lst *cmd_lst);

/*		--> UTILS ALL				*/
void			ft_free_tab(char **tab);
void			ft_free_child(t_big_struct *big_struct, int i);
void			ft_free_between(t_big_struct *big_struct);
char			*ft_strnstr_exec(char *s1, char *s2, size_t n);

/*		--> UTILS EXEC				*/
void			ft_wait(t_big_struct *big_struct);
char			*ft_find_check_path(t_big_struct *big_struct, char **spaced_cmd);
char			*ft_check_slash(t_big_struct *big_struct);
int				ft_strcmp(char *s1, char *s2);

/*		--> BUILTIN				*/
int				ft_pwd(t_big_struct *big_struct, t_cmd_lst *cmd_lst);
int				ft_echo(t_big_struct *big_struct, t_cmd_lst *cmd_lst);
int				ft_cd(t_big_struct *big_struct, t_cmd_lst *cmd_lst);
int				ft_export(t_big_struct *big_s, t_cmd_lst *cmd_lst);
int				ft_unset(t_big_struct *big_struct, t_cmd_lst *cmd_lst);
void			ft_exit(t_big_struct *big_struct);

/*			->utils				*/
void			ft_update_oldpwd(t_big_struct *big_struct, char *s);
char			*ft_get_home(t_big_struct *big_struct, char *env);
int				ft_count_tab(char **tab);
int				ft_check_echo_n(char *s);

/*		--> EXPORT				*/
void			ft_conc_update(t_big_struct *big_s, char **var, char **cmd, int ind);
char			**ft_split_export(char *var, char c);
char			**trim_conc_export(char *var);
char			*ft_remv_eq(char *var);
char			*ft_remv_qt_exp(char *var);
int				parsing_export(char *var);
/*			-> tools			*/
int				ft_eq_check(char *str);
char			*ft_remv_eq(char *var);
char			*ft_remv_qt_exp(char *var);
char			**ft_addback_tab(t_big_struct *big_s, char **envp, char *to_add);
/*			-> exportprint			*/
char			**add_qt_env(char **strs);
char			*ft_dup_special(char *src);
void			ft_print_export_env(t_big_struct *big_s);
void			sort_n_print_exp(char **strs, t_big_struct *big_s);
void			ft_swap(char **strs, int i, int j);

/*		--> HEREDOC, APPEND & REDIREC		*/
void			ft_heredoc_main(t_big_struct *big_struct, t_cmd_lst *cmd_lst, int i);
pid_t			ft_heredoc(t_big_struct *big_struct, t_cmd_lst *cmd_lst, int i);
void			ft_open_heredoc(t_big_struct *big_struct);

/*			->utils				*/
char			*ft_strnstr_hd(char *s1, char *s2, size_t n, size_t i);
int				get_next_heredoc(char *s1, char *s2, int i);

/*		--> SIGNALS							*/
void			sig_handler(int intSig);
void			sig_handler_cmd(int intSig);
void			sig_handler_heredoc(int intSig);
void			get_value(t_big_struct *big_struct, t_cmd_lst *cmd_lst, int i);

/********************************************************/
/********************************************************/
#endif
