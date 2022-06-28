/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:58:00 by ldinaut           #+#    #+#             */
/*   Updated: 2022/06/28 11:33:06 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	last_exec(t_big_struct *big_struct, t_cmd_lst *cmd_lst)
{
	if (big_struct->spaced_cmd != NULL)
	{
		ft_free_tab(big_struct->spaced_cmd);
		big_struct->spaced_cmd = NULL;
	}
	big_struct->spaced_cmd = ft_split(cmd_lst->command, ' ');
	cmd_lst->pid = fork();
	if (cmd_lst->pid == 0)
	{
		if (cmd_lst->fd_in == 0)
			cmd_lst->fd_in = big_struct->pipefd[0];
		if (!ft_check_builtin_multi(big_struct, cmd_lst))
		{
			if (ft_find_check_path(big_struct, big_struct->spaced_cmd) != NULL)
			{
				dup2(cmd_lst->fd_in, 0);
				dup2(cmd_lst->fd_out, 1);
				execve(big_struct->cmd_updated, big_struct->spaced_cmd, big_struct->envp);
			}
		}
		ft_free_tab(big_struct->spaced_cmd);
		big_struct->spaced_cmd = NULL;
		ft_free_child(big_struct);
		exit(1);
	}
	// free(big_struct->spaced_cmd);
	close(big_struct->pipefd[0]);
	if (cmd_lst->fd_in != 0)
		close(cmd_lst->fd_in);
	if (cmd_lst->fd_out != 1)
		close(cmd_lst->fd_out);
}

void	middle_exec(t_big_struct *big_struct, t_cmd_lst *cmd_lst)
{
	// pid_t	pid;
	int		fd_temp;

	if (big_struct->spaced_cmd != NULL)
	{
		ft_free_tab(big_struct->spaced_cmd);
		big_struct->spaced_cmd = NULL;
	}
	big_struct->spaced_cmd = ft_split(cmd_lst->command, ' ');
	fd_temp = big_struct->pipefd[0];
	pipe(big_struct->pipefd);
	cmd_lst->pid = fork();
	if (cmd_lst->pid == 0)
	{
		if (cmd_lst->fd_in == 0)
			cmd_lst->fd_in = fd_temp;
		if (cmd_lst->fd_out == 1)
		{
			close(big_struct->pipefd[0]);
			cmd_lst->fd_out = big_struct->pipefd[1];
		}
		if (!ft_check_builtin_multi(big_struct, cmd_lst))
		{
			if (ft_find_check_path(big_struct, big_struct->spaced_cmd) != NULL)
			{
				dup2(cmd_lst->fd_in, 0);
				dup2(cmd_lst->fd_out, 1);
				execve(big_struct->cmd_updated, big_struct->spaced_cmd, big_struct->envp);
				perror("execve");
			}
		}
		ft_free_tab(big_struct->spaced_cmd);
		big_struct->spaced_cmd = NULL;
		ft_free_child(big_struct);
		exit(1);
	}
	close(big_struct->pipefd[1]);
	close(fd_temp);
	if (cmd_lst->fd_in != 0)
		close(cmd_lst->fd_in);
	if (cmd_lst->fd_out != 1)
		close(cmd_lst->fd_out);
}

void	first_exec(t_big_struct *big_struct, t_cmd_lst *cmd_lst)
{
	if (big_struct->spaced_cmd != NULL)
	{
		ft_free_tab(big_struct->spaced_cmd);
		big_struct->spaced_cmd = NULL;
	}
	big_struct->spaced_cmd = ft_split(cmd_lst->command, ' ');
	cmd_lst->pid = fork();
	if (cmd_lst->pid == 0)
	{
		if (cmd_lst->fd_out == 1)
		{
			close(big_struct->pipefd[0]);
			cmd_lst->fd_out = big_struct->pipefd[1];
		}
		if (!ft_check_builtin_multi(big_struct, cmd_lst))
		{
			if (ft_find_check_path(big_struct, big_struct->spaced_cmd) != NULL)
			{
				dup2(cmd_lst->fd_in, 0);
				dup2(cmd_lst->fd_out, 1);
				execve(big_struct->cmd_updated, big_struct->spaced_cmd, big_struct->envp);
				perror("execve");
			}
		}
		close(big_struct->pipefd[1]);
		ft_free_tab(big_struct->spaced_cmd);
		big_struct->spaced_cmd = NULL;
		ft_free_child(big_struct);
		exit(1);
	}
	close(big_struct->pipefd[1]);
	if (cmd_lst->fd_in != 0)
		close(cmd_lst->fd_in);
	if (cmd_lst->fd_out != 1)
		close(cmd_lst->fd_out);
}

void	ft_wait(int max, t_big_struct *big_struct)
{
	//int	i;
	(void)max;
	t_cmd_lst	*cmd_lst;

	cmd_lst = big_struct->cmd_lst;
	//i = 0;
	//while (i < max)
	//{
		while (cmd_lst)
		{
			waitpid(cmd_lst->pid, &big_struct->status, 0);
			WEXITSTATUS(big_struct->status);
			cmd_lst = cmd_lst->next;
		}
	//	i++;
	//}
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
	first_exec(big_struct, head);
	head = head->next;
	while (i < (n_cmd - 2))
	{
		middle_exec(big_struct, head);
		i++;
		head = head->next;
	}
	last_exec(big_struct, head);
	ft_wait(n_cmd, big_struct);
}
