/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:22:19 by ldinaut           #+#    #+#             */
/*   Updated: 2022/06/23 18:25:40 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc(t_big_struct *big_struct)
{
	int			i;
	t_cmd_lst	*head;

	i = 0;
	head = big_struct->cmd_lst;
	while (head)
	{
		if (ft_strnstr_hd(head->command, "<<", ft_strlen(head->command), i))
		{
			while (get_next_heredoc(head->command, "<<", i) > 0)
			{
				printf("strnstr = %s\n ", ft_strnstr_hd(head->command, "<<", ft_strlen(head->command), i));
				i = (get_next_heredoc(head->command, "<<", i));
			}
		}
		i = 0;
		head = head->next;
	}
}

int	ft_simple_exec(t_big_struct *big_struct, t_cmd_lst *cmd_lst)
{
	pid_t	pid;

	big_struct->spaced_cmd = ft_split(big_struct->cmd_lst->command, ' ');
	if (!ft_check_builtin_multi(big_struct, cmd_lst))
	{
		pid = fork();
		if (pid == 0)
		{
			if (ft_find_check_path(big_struct, big_struct->spaced_cmd) != NULL)
			{
				dup2(cmd_lst->fd_in, 0);
				dup2(cmd_lst->fd_out, 1);
				execve(big_struct->cmd_updated, big_struct->spaced_cmd, big_struct->envp);
				perror("execve");
			}
			ft_free_tab(big_struct->spaced_cmd);
			ft_free_child(big_struct);
			exit(1);
		}
	}
	if (cmd_lst->fd_in != 0)
		close(cmd_lst->fd_in);
	if (cmd_lst->fd_out != 1)
		close(cmd_lst->fd_out);
	return (0);
}

void	ft_exec(t_big_struct *big_struct)
{
	t_cmd_lst	*head;
//	t_cmd_lst	*head_tmp;

	head = big_struct->cmd_lst;
/*	head_tmp = big_struct->cmd_lst;
	while (head_tmp && head_tmp->command)
	{
		head_tmp = head_tmp->next;
	}*/
	if (head->command && ft_strnstr_exec(head->command, "<<", ft_strlen(head->command)))
		ft_heredoc(big_struct);
	if (head && !head->next)
	{
		ft_simple_exec(big_struct, head);
		wait(NULL);
	}
	else if (head && head->next)
	{
		ft_multi_pipe(big_struct);
	}
}
