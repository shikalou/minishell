/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:58:00 by ldinaut           #+#    #+#             */
/*   Updated: 2022/07/06 16:36:32 by ldinaut          ###   ########.fr       */
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
	if (big_struct->spaced_cmd[0] == NULL)
		return ;
	cmd_lst->pid = fork();
	if (cmd_lst->pid == 0)
	{
		if (cmd_lst->fd_in == 0)
			cmd_lst->fd_in = big_struct->pipefd[0];
		if (ft_check_builtin_multi(big_struct, cmd_lst) == 0)
		{
			if (ft_find_check_path(big_struct, big_struct->spaced_cmd) != NULL)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, sig_handler_cmd);
				dup2(cmd_lst->fd_in, 0);
				dup2(cmd_lst->fd_out, 1);
				execve(big_struct->cmd_updated, big_struct->spaced_cmd, big_struct->envp);
			}
		}
		ft_free_tab(big_struct->spaced_cmd);
		big_struct->spaced_cmd = NULL;
		ft_free_child(big_struct);
		exit(127);
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
	int		fd_temp;

	if (big_struct->spaced_cmd != NULL)
	{
		ft_free_tab(big_struct->spaced_cmd);
		big_struct->spaced_cmd = NULL;
	}
	big_struct->spaced_cmd = ft_split(cmd_lst->command, ' ');
	if (big_struct->spaced_cmd[0] == NULL)
		return ;
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
		if (ft_check_builtin_multi(big_struct, cmd_lst) == 0)
		{
			if (ft_find_check_path(big_struct, big_struct->spaced_cmd) != NULL)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, sig_handler_cmd);
				dup2(cmd_lst->fd_in, 0);
				dup2(cmd_lst->fd_out, 1);
				execve(big_struct->cmd_updated, big_struct->spaced_cmd, big_struct->envp);
				perror("execve");
			}
		}
		ft_free_tab(big_struct->spaced_cmd);
		big_struct->spaced_cmd = NULL;
		ft_free_child(big_struct);
		exit(127);
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
	if (big_struct->spaced_cmd[0] == NULL)
		return ;
	cmd_lst->pid = fork();
	if (cmd_lst->pid == 0)
	{
		if (cmd_lst->fd_out == 1)
		{
			close(big_struct->pipefd[0]);
			cmd_lst->fd_out = big_struct->pipefd[1];
		}
		if (ft_check_builtin_multi(big_struct, cmd_lst) == 0)
		{
			if (ft_find_check_path(big_struct, big_struct->spaced_cmd) != NULL)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, sig_handler_cmd);
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
		exit(127);
	}
	close(big_struct->pipefd[1]);
	if (cmd_lst->fd_in != 0)
		close(cmd_lst->fd_in);
	if (cmd_lst->fd_out != 1)
		close(cmd_lst->fd_out);
}

void	ft_wait(t_big_struct *big_struct)
{
	t_cmd_lst	*cmd_lst;

	cmd_lst = big_struct->cmd_lst;
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

void	ft_multi_pipe(t_big_struct *big_struct)
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
	ft_wait(big_struct);
}
