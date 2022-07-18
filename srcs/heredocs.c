/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 15:29:57 by ldinaut           #+#    #+#             */
/*   Updated: 2022/07/18 13:00:25 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_open_heredoc(t_big_struct *b, t_cmd_lst *cmd_lst)
{
	char	file[10];
	char	c[100];
	int		fd_rand;
	int		i;
	int		j;

	fd_rand = open("/dev/urandom", O_RDONLY);
	i = read(fd_rand, c, 100);
	c[i] = '\0';
	i = 0;
	j = 0;
	while (j < 11)
	{
		if (ft_isalpha(c[i]))
		{
			file[j] = c[i];
			j++;
		}
		i++;
	}
	file[j] = '\0';
	close(fd_rand);
	b->random_file = ft_strjoin("/tmp/", file);
	cmd_lst->fd_in = open(b->random_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
}

int	ft_heredoc(t_big_struct *b, t_cmd_lst *cmd_lst, int i)
{
	char	*input;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, sig_handler_heredoc);
		input = readline("> ");
		while (input && ft_strcmp(input, b->spaced_par[i]) != 0)
		{
			write(cmd_lst->fd_in, input, ft_strlen(input));
			write(cmd_lst->fd_in, "\n", 1);
			free(input);
			input = readline("> ");
		}
		if (!input)
		{
			printf("warning: here_doc delimited by EOF (wanted `%s')\n",
				b->spaced_par[i]);
		}
		close(cmd_lst->fd_in);
		ft_free_child(b, 0);
		exit(0);
	}
	return (pid);
}

void	ft_firstcheck(t_big_struct *b, t_cmd_lst *cmd_lst)
{
	if (cmd_lst->fd_in != 0)
		close(cmd_lst->fd_in);
	if (b->random_file != NULL)
	{
		unlink(b->random_file);
		free(b->random_file);
		b->random_file = NULL;
	}
}

void	ft_heredoc_main(t_big_struct *b, t_cmd_lst *cmd_lst, int i)
{
	pid_t	pid;

	get_value(b, cmd_lst, 0);
	signal(SIGINT, SIG_IGN);
	ft_firstcheck(b, cmd_lst);
	ft_open_heredoc(b, cmd_lst);
	pid = ft_heredoc(b, cmd_lst, i);
	waitpid(pid, &b->status, 0);
	close(cmd_lst->fd_in);
	if (WEXITSTATUS(b->status) == 2)
	{
		ft_free_tab(b->spaced_par);
		b->spaced_par = NULL;
		ft_lstclear_cmd(b->cmd_lst);
		b->cmd_lst = NULL;
		b->status = 130;
	}
	else
		cmd_lst->fd_in = open(b->random_file, O_RDONLY, 0644);
}
