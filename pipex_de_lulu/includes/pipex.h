/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:41:15 by ldinaut           #+#    #+#             */
/*   Updated: 2022/03/25 14:03:54 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include "../ft_printf/ft_printf.h"
# include "../gnl/get_next_line_bonus.h"

typedef struct s_cmd
{
	int		pipefd[2];
	int		fd_temp;
	int		infile;
	int		outfile;

	char	**path_tab;
	char	**arg_path;

	char	*path;
	char	*limiter;

}	t_cmd;

t_cmd	*ft_init_struct(char **envp);

void	ft_exec_one(t_cmd *cmd, char **argv, char **envp);
void	ft_exec_middle(t_cmd *cmd, char *argv, char **envp);
void	ft_exec_last(t_cmd *cmd, char *argv, char **envp);
void	ft_free_struct(t_cmd *cmd);
void	ft_free_path_tab(t_cmd *cmd);
void	ft_free_arg_path(t_cmd *cmd);
void	ft_here_doc(int argc, char **argv, t_cmd *cmd, char **envp);
void	ft_wait(int argc);
void	ft_close(t_cmd *cmd, int i);
void	ft_dup(t_cmd *cmd);
void	ft_exit(t_cmd *cmd);

char	*ft_find_path(char **envp);
char	*ft_find_check_path(t_cmd *cmd);
char	*ft_check_slash(t_cmd *cmd);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);

size_t	ft_strlen(const char *str);

int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_open(t_cmd *cmd, char **argv, int argc);

char	**ft_split(char const *s1, char c);

#endif