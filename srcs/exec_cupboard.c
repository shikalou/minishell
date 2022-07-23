/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cupboard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 12:24:26 by ldinaut           #+#    #+#             */
/*   Updated: 2022/07/23 14:53:50 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_sz_spacer(char *old, int i)
{
	int		j;
	int		check;

	check = 0;
	while (old && old[i])
	{
		j = i + 1;
		if (old[i] == '"' && old[j] && old[j] == '"' && old[j + 1]
			&& old[j + 1] != ' ')
		{
			check++;
			i += 2;
		}
		else if (old[i] == '\'' && old[j] && old[j] == '\'' && old[j + 1]
			&& old[j + 1] != ' ')
		{
			check++;
			i += 2;
		}
		else
			i++;
	}
	return (i + check);
}

char	*qt_spacer(char *old, int i)
{
	int		j;
	size_t	size;
	char	*result;

	size = get_sz_spacer(old, 0);
	j = 0;
	if (!old || size == ft_strlen(old))
		return (old);
	result = malloc(sizeof(char) * size + 1);
	if (!result)
		return (NULL);
	while (old && old[i])
	{
		if (old[i] == '"' && old[i + 1] && old[i + 1] == '"' && old[i + 2]
			&& old[i + 2] != ' ')
		{
			result[j++] = old[i++];
			result[j++] = old[i++];
			result[j++] = ' ';
		}
		else if (old[i] == '\'' && old[i + 1] && old[i + 1] == '\''
			&& old[i + 2] && old[i + 2] != ' ')
		{
			result[j++] = old[i++];
			result[j++] = old[i++];
			result[j++] = ' ';
		}
		else
			result[j++] = old[i++];
	}
	result[j] = '\0';
	free(old);
	return (result);
}

void	malloc_spaced_cmd(t_big *b, t_cmd_lst *cmd_lst)
{
	int	i;

	i = 0;	
	if (b->spaced_cmd != NULL)
	{
		ft_free_tab(b->spaced_cmd);
		b->spaced_cmd = NULL;
	}
	while (cmd_lst->command[i] == ' ')
		i++;
	if ((int)ft_strlen(cmd_lst->command) == i)
	{
		free(cmd_lst->command);
		cmd_lst->command = NULL;
	}
	else
		cmd_lst->command = qt_spacer(cmd_lst->command, 0);
	b->spaced_cmd = ft_sdf(cmd_lst->command, ' ');
}

void	exit_child_last_mid(t_big *b, int i)
{
	if (b->spaced_cmd[0] == NULL || i == 1)
	{
		ft_free_tab(b->spaced_cmd);
		b->spaced_cmd = NULL;
		ft_free_child(b, 0);
		exit(0);
	}
	ft_free_tab(b->spaced_cmd);
	b->spaced_cmd = NULL;
	ft_free_child(b, 0);
	exit(127);
}

void	exit_child_first(t_big *b)
{
	if (b->spaced_cmd[0] == NULL)
	{
		close(b->pipefd[1]);
		ft_free_tab(b->spaced_cmd);
		b->spaced_cmd = NULL;
		ft_free_child(b, 0);
		exit(0);
	}
	close(b->pipefd[1]);
	ft_free_tab(b->spaced_cmd);
	b->spaced_cmd = NULL;
	ft_free_child(b, 0);
	exit(127);
}

void	fd_manager_mid(t_big *b, t_cmd_lst *cmd_lst, int fd_temp)
{
	if (cmd_lst->fd_in == 0)
		cmd_lst->fd_in = fd_temp;
	if (cmd_lst->fd_out == 1)
	{
		close(b->pipefd[0]);
		cmd_lst->fd_out = b->pipefd[1];
	}
}
