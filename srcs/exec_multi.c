/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:58:00 by ldinaut           #+#    #+#             */
/*   Updated: 2022/07/19 14:09:08 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	last_exec(t_big *b, t_cmd_lst *cmd_lst)
{
	malloc_spaced_cmd(b, cmd_lst);
	cmd_lst->pid = fork();
	if (cmd_lst->pid == 0)
	{
		if (cmd_lst->fd_in == 0)
			cmd_lst->fd_in = b->pipefd[0];
		if (b->spaced_cmd[0] && ft_check_builtin_multi(b, cmd_lst) == 0)
		{
			if (ft_find_check_path(b, b->spaced_cmd) != NULL)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, sig_handler_cmd);
				ft_dup(cmd_lst);
				execve(b->cmd_updated, b->spaced_cmd, b->envp);
				perror("execve");
			}
		}
		exit_child_last_mid(b);
	}
	close(b->pipefd[0]);
	ft_close_fdinout(cmd_lst);
}

void	middle_exec(t_big *b, t_cmd_lst *cmd_lst)
{
	int		fd_temp;

	malloc_spaced_cmd(b, cmd_lst);
	fd_temp = b->pipefd[0];
	pipe(b->pipefd);
	cmd_lst->pid = fork();
	if (cmd_lst->pid == 0)
	{
		fd_manager_mid(b, cmd_lst, fd_temp);
		if (b->spaced_cmd[0] && ft_check_builtin_multi(b, cmd_lst) == 0)
		{
			if (ft_find_check_path(b, b->spaced_cmd) != NULL)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, sig_handler_cmd);
				ft_dup(cmd_lst);
				execve(b->cmd_updated, b->spaced_cmd, b->envp);
				perror("execve");
			}
		}
		exit_child_last_mid(b);
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
			if (ft_find_check_path(b, b->spaced_cmd) != NULL)
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

void	ft_wait(t_big *big_struct, t_cmd_lst *cmd_lst)
{
	while (cmd_lst)
	{
		if (cmd_lst->next == NULL)
		{
			waitpid(cmd_lst->pid, &big_struct->status, 0);
			if (WIFSIGNALED(big_struct->status))
			{
				if (WCOREDUMP(big_struct->status))
					printf("Quit (core dumped)\n");
				big_struct->status = (WTERMSIG(big_struct->status) + 128);
				if (big_struct->status == 130)
					printf("\n");
			}
			else
				big_struct->status = WEXITSTATUS(big_struct->status);
		}
		waitpid(cmd_lst->pid, &big_struct->status, 0);
		if (WIFSIGNALED(big_struct->status))
			big_struct->status = WTERMSIG(big_struct->status);
		else
			big_struct->status = WEXITSTATUS(big_struct->status);
		cmd_lst = cmd_lst->next;
	}
}

void	ft_multi_pipe(t_big *big_struct)
{
	t_cmd_lst	*head;
	int			i;
	int			n_cmd;

	head = big_struct->cmd_lst;
	i = 0;
	n_cmd = ft_lstsize_cmd(big_struct->cmd_lst);
	pipe(big_struct->pipefd);
	if (head->fd_in != -1)
		first_exec(big_struct, head);
	else
		close(big_struct->pipefd[1]);
	head = head->next;
	while (i < (n_cmd - 2))
	{
		middle_exec(big_struct, head);
		i++;
		head = head->next;
	}
	last_exec(big_struct, head);
	head = big_struct->cmd_lst;
	ft_wait(big_struct, head);
}
