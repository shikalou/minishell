/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:22:19 by ldinaut           #+#    #+#             */
/*   Updated: 2022/06/22 18:45:48 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc(t_big_struct *big_struct)
{
	int		i;
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
	int			pid;

	big_struct->spaced_cmd = ft_split(big_struct->cmd_lst->command, ' ');
	if (!ft_check_builtin(big_struct, cmd_lst))
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
			//ft_free_tab(big_struct->spaced_cmd);
			//ft_free_bs(big_struct);
			exit(1);
		}
	}
	if (cmd_lst->fd_in != 0)
		close(cmd_lst->fd_in);
	if (cmd_lst->fd_out != 1)
		close(cmd_lst->fd_out);
	return (0);
}

int	ft_check_builtin(t_big_struct *big_struct, t_cmd_lst *cmd_lst)
{
	if (cmd_lst->command && ft_memcmp(big_struct->spaced_cmd[0], "pwd", 3) == 0)
	{
		ft_pwd(big_struct, cmd_lst);
		return (1);
	}
	else if (cmd_lst->command && ft_memcmp(big_struct->spaced_cmd[0], "echo", 4) == 0)
	{
		ft_echo(big_struct, cmd_lst);
		return (1);
	}
	if (cmd_lst->command && ft_memcmp(big_struct->spaced_cmd[0], "cd", 2) == 0)
	{
		ft_cd(big_struct, cmd_lst);
		return (1);
	}
	if (cmd_lst->command && ft_memcmp(big_struct->spaced_cmd[0], "export", 6) == 0)
		return (ft_export(big_struct, cmd_lst));

	/*else if (cmd_lst->command && ft_memcmp(big_struct->spaced_cmd[0], "unset", size) == 0)
		return (ft_unset(big_struct, cmd_lst));*/
	//else if (les prochains builtins :D )
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
