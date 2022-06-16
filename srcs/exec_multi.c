/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:58:00 by ldinaut           #+#    #+#             */
/*   Updated: 2022/06/16 13:35:14 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	last_exec(t_big_struct *big_struct, t_cmd_lst *cmd_lst)
{
	pid_t	pid;

	if (big_struct->spaced_cmd != NULL)
	{
		ft_free_tab(big_struct->spaced_cmd);
		big_struct->spaced_cmd = NULL;
	}
	big_struct->spaced_cmd = ft_split(cmd_lst->command, ' ');
	pid = fork();
	if (pid == 0)
	{
		if (ft_find_check_path(big_struct, big_struct->spaced_cmd) != NULL)
		{
			if (cmd_lst->fd_in != 0)
				dup2(cmd_lst->fd_in, 0);
			else
				dup2(big_struct->pipefd[0], 0);
			dup2(cmd_lst->fd_out, 1);
			execve(big_struct->cmd_updated, big_struct->spaced_cmd, big_struct->envp);
		}
		exit(1);
	}
	//free(big_struct->spaced_cmd);
	close(big_struct->pipefd[0]);
	//close fd out si on l'a mofidie
	//close fd_in si on l'a modifie
}

void	middle_exec(t_big_struct *big_struct, t_cmd_lst *cmd_lst)
{
	pid_t	pid;
	int		fd_temp;

	if (big_struct->spaced_cmd != NULL)
	{
		ft_free_tab(big_struct->spaced_cmd);
		big_struct->spaced_cmd = NULL;
	}
	big_struct->spaced_cmd = ft_split(cmd_lst->command, ' ');
	fd_temp = big_struct->pipefd[0];
	pipe(big_struct->pipefd);
	pid = fork();
	if (pid == 0)
	{
		if (ft_find_check_path(big_struct, big_struct->spaced_cmd) != NULL)
		{
			if (cmd_lst->fd_in != 0)
				dup2(cmd_lst->fd_in, 0);
			else
				dup2(fd_temp, 0);
			if (cmd_lst->fd_out != 1)
				dup2(cmd_lst->fd_out, 1);
			else
			{
				close(big_struct->pipefd[0]);
				dup2(big_struct->pipefd[1], 1);
			}
			execve(big_struct->cmd_updated, big_struct->spaced_cmd, big_struct->envp);
			perror("execve");
		}
		exit(1);
	}
	close(big_struct->pipefd[1]);
	close(fd_temp);
	// close fd_in si modifie
	// close fd_out si modifie
}

void	first_exec(t_big_struct *big_struct, t_cmd_lst *cmd_lst)
{
	pid_t	pid;

	if (big_struct->spaced_cmd != NULL)
	{
		ft_free_tab(big_struct->spaced_cmd);
		big_struct->spaced_cmd = NULL;
	}
	big_struct->spaced_cmd = ft_split(cmd_lst->command, ' ');
	pid = fork();
	if (pid == 0)
	{
		if (ft_find_check_path(big_struct, big_struct->spaced_cmd) != NULL)
		{
			dup2(cmd_lst->fd_in, 0);
			if (cmd_lst->fd_out != 1)
				dup2(cmd_lst->fd_out, 1);
			else
			{
				close(big_struct->pipefd[0]);
				dup2(big_struct->pipefd[1], 1);
			}
			execve(big_struct->cmd_updated, big_struct->spaced_cmd, big_struct->envp);
			perror("execve");
		}
		exit(1);
	}
	close(big_struct->pipefd[1]);
	//close fd out si on l'a mofidie
	//close fd_in si on l'a modifie
}

void	ft_wait(int	max)
{
	int	i;

	i = 0;
	while (i < max)
	{
		wait(NULL);
		i++;
	}
}

void	ft_multi_pipe(t_big_struct *big_struct)
{
	t_cmd_lst	*head;
	int			i;
	int			n_cmd;

	head = big_struct->cmd_lst;
	i = 0;
	n_cmd = ft_lstsize_cmd(big_struct->cmd_lst);
	pipe(big_struct->pipefd);
	if (!ft_check_builtin(big_struct))
		first_exec(big_struct, head);
	head = head->next;
	while (i < (n_cmd - 2))
	{
		if (!ft_check_builtin(big_struct))
			middle_exec(big_struct, head);
		i++;
		head = head->next;
	}
	if (!ft_check_builtin(big_struct))
		last_exec(big_struct, head);
	ft_wait(n_cmd);
}
