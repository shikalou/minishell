/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 15:29:57 by ldinaut           #+#    #+#             */
/*   Updated: 2022/07/06 15:12:22 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_open_heredoc(t_big_struct *big_struct)
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
	big_struct->random_file = ft_strjoin("/tmp/", file);
}

int	ft_heredoc(t_big_struct *big_struct, t_cmd_lst *cmd_lst, int i)
{
	char	*input;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		//signal(SIGINT, sig_handler_heredoc);
		input = readline("> ");
		if (!input)
		{
			printf("warning: here_doc delimited by end-of-file (wanted `%s')\n", big_struct->spaced_par[i]);
			i = -1;
		}
		while (i != -1 && ft_strcmp(input, big_struct->spaced_par[i]) != 0)
		{
			write(cmd_lst->fd_in, input, ft_strlen(input));
			write(cmd_lst->fd_in, "\n", 1);
			free(input);
			input = readline("> ");
			if (!input)
			{
				printf("warning: here_doc delimited by end-of-file (wanted `%s')\n", big_struct->spaced_par[i]);
				break ;
			}
		}
		exit(0);
	}
	return (pid);
}

void	ft_heredoc_main(t_big_struct *big_struct, t_cmd_lst *cmd_lst, int i)
{
	pid_t	pid;

	if (cmd_lst->fd_in != 0)
		close(cmd_lst->fd_in);
	if (big_struct->random_file != NULL)
	{
		unlink(big_struct->random_file);
		free(big_struct->random_file);
		big_struct->random_file = NULL;
	}
	ft_open_heredoc(big_struct);
	cmd_lst->fd_in = open(big_struct->random_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	pid = ft_heredoc(big_struct, cmd_lst, i);
	waitpid(pid, &big_struct->status, 0);
	close(cmd_lst->fd_in);
	cmd_lst->fd_in = open(big_struct->random_file, O_RDONLY, 0644);
}
