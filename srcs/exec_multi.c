/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:58:00 by ldinaut           #+#    #+#             */
/*   Updated: 2022/07/24 16:48:30 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	last_exec(t_big *b, t_cmd_lst *cmd_lst)
{
	int	i;

	malloc_spaced_cmd(b, cmd_lst);
	cmd_lst->pid = fork();
	if (cmd_lst->pid == 0)
	{
		if (cmd_lst->fd_in == 0)
			cmd_lst->fd_in = b->pipefd[0];
		i = ft_check_builtin_multi(b, cmd_lst);
		if (b->spaced_cmd[0] && i == 0)
		{
			if (ft_find_check_path(b, b->spaced_cmd, -1) != NULL)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, sig_handler_cmd);
				ft_dup(cmd_lst);
				execve(b->cmd_updated, b->spaced_cmd, b->envp);
				perror("execve");
			}
		}
		exit_child_last_mid(b, i);
	}
	close(b->pipefd[0]);
	ft_close_fdinout(cmd_lst);
}

void	middle_exec(t_big *b, t_cmd_lst *cmd_lst, int i, int fd_temp)
{
	malloc_spaced_cmd(b, cmd_lst);
	pipe(b->pipefd);
	cmd_lst->pid = fork();
	if (cmd_lst->pid == 0)
	{
		fd_manager_mid(b, cmd_lst, fd_temp);
		i = ft_check_builtin_multi(b, cmd_lst);
		if (b->spaced_cmd[0] && i == 0)
		{
			if (ft_find_check_path(b, b->spaced_cmd, -1) != NULL)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, sig_handler_cmd);
				ft_dup(cmd_lst);
				execve(b->cmd_updated, b->spaced_cmd, b->envp);
				perror("execve");
			}
		}
		exit_child_last_mid(b, i);
	}
	close(b->pipefd[1]);
	close(fd_temp);
	ft_close_fdinout(cmd_lst);
}

void	first_exec(t_big *b, t_cmd_lst *cmd_lst)
{
	malloc_spaced_cmd(b, cmd_lst);
	cmd_lst->pid = fork();
	if (cmd_lst->pid == 0)
	{
		if (cmd_lst->fd_out == 1)
		{
			close(b->pipefd[0]);
			cmd_lst->fd_out = b->pipefd[1];
		}
		if (b->spaced_cmd[0] && ft_check_builtin_multi(b, cmd_lst) == 0)
		{
			if (ft_find_check_path(b, b->spaced_cmd, -1) != NULL)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, sig_handler_cmd);
				ft_dup(cmd_lst);
				execve(b->cmd_updated, b->spaced_cmd, b->envp);
				perror("execve");
			}
		}
		exit_child_first(b);
	}
	close(b->pipefd[1]);
	ft_close_fdinout(cmd_lst);
}

void	ft_wait(t_big *b, t_cmd_lst *cmd_lst)
{
	while (cmd_lst)
	{
		if (cmd_lst->next == NULL)
		{
			waitpid(cmd_lst->pid, &b->status, 0);
			if (WIFSIGNALED(b->status))
			{
				b->status = (WTERMSIG(b->status) + 128);
				ft_check_signal(b->status);
			}
			else
				b->status = WEXITSTATUS(b->status);
			break ;
		}
		waitpid(cmd_lst->pid, &b->status, 0);
		if (WIFSIGNALED(b->status) && WIFSIGNALED(b->status) != 1)
			b->status = WTERMSIG(b->status) + 128;
		else
			b->status = WEXITSTATUS(b->status);
		cmd_lst = cmd_lst->next;
	}
}

void	ft_multi_pipe(t_big *b)
{
	t_cmd_lst	*head;
	int			i;
	int			n_cmd;

	head = b->cmd_lst;
	i = 0;
	n_cmd = ft_lstsize_cmd(b->cmd_lst);
	pipe(b->pipefd);
	if (head->fd_in != -1)
		first_exec(b, head);
	else
		close(b->pipefd[1]);
	head = head->next;
	while (i < (n_cmd - 2))
	{
		middle_exec(b, head, 0, b->pipefd[0]);
		i++;
		head = head->next;
	}
	last_exec(b, head);
	head = b->cmd_lst;
	ft_wait(b, head);
}
