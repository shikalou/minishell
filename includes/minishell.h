/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:47:27 by ldinaut           #+#    #+#             */
/*   Updated: 2022/07/21 15:14:30 by mcouppe          ###   ########.fr       */
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

typedef struct s_sdf
{
	int			k;
	int			i;
	int			j;
	int			l;
	const char	*s;
	char		c;
	char		**strs;

}	t_sdf;

typedef struct s_big_struct
{
	char		**input;
	char		**envp;
	char		**path;
	char		**spaced_cmd;
	char		**spaced_par;
	char		*absolut_path;
	char		*cmd_updated;
	int			check_export;
	int			check_unset;
	int			env_size;
	int			pipefd[2];
	int			status;
	int			name_s;
	char		*c_status;
	char		*random_file;
	t_env_lst	*env_lst;
	t_cmd_lst	*cmd_lst;
}	t_big;

/********************************************************/
/***********INIT AND START*******************************/
/********************************************************/
void			shellmini(t_big *big_struct);

t_big			*ft_init_big(char **envp);

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
int				ft_lstsize_env(t_env_lst *lst);
char			**ft_new_envp(t_env_lst *env_lst);

/********************************************************/
/*************PARSING************************************/
/********************************************************/
int				ft_parsing(char *cmd, t_big *big_struct);

/*		--> PARSING QUOTES			*/
void			parsing_quotes(t_big *big_struct);

char			*expand_first_case(t_big *big_s, int i, char *cmd);
char			*expand_second_case(t_big *big_s, int i, char *cmd);
char			*extended_dollar(char *cmd, t_big *big_struct);
char			*fill_cmd_expand(char *cmd, t_big *big_struct, char *up, int j);
char			*ft_get_env_var(t_big *big_struct, char *cmd, int index);
char			*get_env_lst(char *cmd, int i, int j, t_big *big_struct);
char			*strtrim_aug(char *cmd, int check);
int				ft_len_dollar(char *cmd, int i);
int				ft_memchr_aug(char *s, int i, char c);
int				strtrim_size(char *cmd, int check);

/*		--> PARSING REDIRECTIONS	*/
void			parsing_redirection(t_big *big_struct, int i);
void			redirect_heredoc(t_big *b, t_cmd_lst *cmd_lst, int i);
void			redirect_in(t_big *b, t_cmd_lst *cmd_lst, int i);
void			redirect_out(t_big *b, t_cmd_lst *cmd_lst, int i, int j);
char			*update_flux(t_big *b, int size, int index);

/*		--> UTILS PARSING			*/
void			ft_init_sdf(t_sdf *sdf, const char *s1, char c);
void			parsing_trash(t_big *big_s);
char			**ft_sdf(char const *s1, char c);
char			*add_space(char *cmd, int index);
char			*add_space_hereapp(char *cmd, int index);
char			*check_spe_char(char *cmd, int len_tmp);
int				check_after_pipe(char *cmd, char c);
int				check_char(char c);
int				check_str(char *cmd, int index, int end);
int				check_char_basic(char c);
int				ft_checkquotes(char *cmd);
int				ft_count_char(char const *s1, int i, char c);
int				ft_count_strs(char const *s, char c);
int				ft_split_quotes(const char *s1, int i);

/********************************************************/
/*************SHLVL**************************************/
/********************************************************/
int				ft_update_shlvl(t_big *big_s);
char			**shlvl_envp(t_big *big_s, int ind);
char			*get_nb_shlvl(char *line, int ind);
char			*shlvl_line(t_env_lst *env);

/********************************************************/
/*************EXECUTION**********************************/
/********************************************************/
void			ft_exec(t_big *big_struct);
void			ft_multi_pipe(t_big *big_struct);
void			first_exec(t_big *big_struct, t_cmd_lst *cmd_lst);
void			middle_exec(t_big *big_struct, t_cmd_lst *cmd_lst);
void			last_exec(t_big *big_struct, t_cmd_lst *cmd_lst);
int				ft_simple_exec(t_big *big_s, t_cmd_lst *cmd_lst);
int				ft_check_builtin_multi(t_big *big_s, t_cmd_lst *cmd_lst);

/*		--> UTILS ALL				*/
void			ft_free_tab(char **tab);
void			ft_free_child(t_big *big_struct, int i);
void			ft_free_between(t_big *big_struct);
char			*ft_strnstr_exec(char *s1, char *s2, size_t n);
void			ft_close_fdinout(t_cmd_lst *cmd_lst);
void			exit_child_first(t_big *b);
void			exit_child_last_mid(t_big *b);
void			fd_manager_mid(t_big *b, t_cmd_lst *cmd_lst, int fd_tmp);

/*		--> UTILS EXEC				*/
void			ft_wait(t_big *big_struct, t_cmd_lst *cmd_lst);
void			ft_dup(t_cmd_lst *cmd_lst);
void			malloc_spaced_cmd(t_big *b, t_cmd_lst *cmd_lst);
void			malloc_spacedcmd_simple(t_big *b);
char			*ft_find_check_path(t_big *b, char **spaced_cmd);
char			*ft_check_slash(t_big *big_struct);
int				ft_strcmp(char *s1, char *s2);

/*		--> BUILTIN				*/
int				ft_cd(t_big *big_struct);
int				ft_echo(t_big *big_s, t_cmd_lst *cmd_lst);
int				ft_env(t_big *big_s, t_cmd_lst *cmd_lst);
int				ft_export(t_big *big_s, t_cmd_lst *cmd_lst);
int				ft_pwd(t_big *big_struct, t_cmd_lst *cmd_lst);
int				ft_unset(t_big *big_struct, t_cmd_lst *cmd_lst);
void			ft_exit(t_big *big_struct);

/*			->utils				*/
void			ft_update_oldpwd(t_big *big_struct, char *s, int i);
char			*ft_get_home(t_big *big_struct, char *env);
int				ft_count_tab(char **tab);
int				ft_check_echo_n(char *s);

/*		--> EXPORT				*/
void			ft_conc_update(t_big *b, char **var, char **cmd, int ind);
void			ft_concenv_up(t_big *b, char **var);
void			ft_cue(t_env_lst *env, char **var, int len_env, char *tmp);
void			ft_up_env_exp(t_big *b, char **var, char **split, int ind);
void			update_exp(t_big *b, char **var, char **cmd, int ind);
char			**ft_split_export(char *var, char c);
char			**trim_conc_export(char *var);
int				exp_update_line(char **var, t_env_lst *env, int i, int j);
int				parsing_export(char *var);
/*			-> tools			*/
int				ft_eq_check(char *str);
int				ft_error_export(t_big *big_s, char *split, int check);
int				updt_e(char **s, int ind, t_big *big, char **var);
void			ft_conc_main(t_env_lst *env, char **var);
void			ft_swap_exp(char **strs, int i, int j);
char			*ft_add_char(char *str, char c);
char			*ft_remv_eq(char *var);
char			*ft_remv_qt_exp(char *var);
char			**add_qt_env(char **strs);
char			**ft_addback_tab(t_big *big_s, char **envp, char *to_add);
/*			-> exportprint			*/
char			*ft_dup_special(char *src);
void			env_print(char **strs, int size, t_cmd_lst *cmd_lst);
void			ft_print_export_env(t_big *big_s, t_cmd_lst *cmd_lst);
void			sort_n_print_exp(char **strs, t_big *big_s, t_cmd_lst *cmd_lst);
void			ft_swap(char **strs, int i, int j);

/*		--> HEREDOC, APPEND & REDIREC		*/
void			ft_heredoc_main(t_big *b, t_cmd_lst *cmd_lst, int i);
pid_t			ft_heredoc(t_big *big_struct, t_cmd_lst *cmd_lst, int i);
void			ft_open_heredoc(t_big *big_struct, t_cmd_lst *cmd_lst);

/*			->utils				*/
char			*ft_strnstr_hd(char *s1, char *s2, size_t n, size_t i);
int				get_next_heredoc(char *s1, char *s2, int i);

/*		--> SIGNALS							*/
void			sig_handler(int intSig);
void			sig_handler_cmd(int intSig);
void			sig_handler_heredoc(int intSig);
void			get_value(t_big *big_struct, t_cmd_lst *cmd_lst, int i);
void			ft_check_signal(int status);

/********************************************************/
/********************************************************/
#endif
