/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 15:29:57 by ldinaut           #+#    #+#             */
/*   Updated: 2022/07/05 15:07:11 by ldinaut          ###   ########.fr       */
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
			i++;
			j++;
		}
		else
			i++;
	}
	file[j] = '\0';
	close(fd_rand);
	big_struct->random_file = ft_strjoin("/tmp/", file);
}

void	ft_heredoc(t_big_struct *big_struct, t_cmd_lst *cmd_lst, int i)
{
	char	*input;
	char	*new;

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
	input = readline("> ");
	while (ft_strcmp(input, big_struct->spaced_par[i]) != 0)
	{
		new = ft_strjoin(input, "\n");
		free(input);
		write(cmd_lst->fd_in, new, ft_strlen(new));
		free(new);
		input = readline("> ");
	}
	close(cmd_lst->fd_in);
	cmd_lst->fd_in = open(big_struct->random_file, O_RDONLY);
}
