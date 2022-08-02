/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cupboard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 12:24:26 by ldinaut           #+#    #+#             */
/*   Updated: 2022/08/02 12:38:30 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	{
		cmd_lst->command = qt_pre_spacer(cmd_lst->command, 0, 0);
		cmd_lst->command = qt_aft_spacer(cmd_lst->command, 0, 0);
	}
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
	if (errno == 13)
		exit (126);
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

void	ft_exit_err(int	noerr)
{
	if (noerr == 13)
		exit (126);
	exit(127);
}