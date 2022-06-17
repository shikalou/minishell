/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:22:19 by ldinaut           #+#    #+#             */
/*   Updated: 2022/06/17 11:59:08 by mcouppe          ###   ########.fr       */
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
	int			i;

	i = 0;
	big_struct->spaced_cmd = ft_split(big_struct->cmd_lst->command, ' ');
	while (big_struct->spaced_cmd[i] != NULL)
	{
		printf("space_cmd[%d] = %s\n", i, big_struct->spaced_cmd[i]);
		i++;
	}
	printf("FD OUT DANS EXEC SI;PLE%d\n", big_struct->cmd_lst->fd_out);
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
		exit(1);
	}
	return (0);
}

int	ft_check_builtin(t_big_struct *big_struct, char *cmd)
{
	t_cmd_lst *head;

	head = big_struct->cmd_lst;
	while (head && head->command)
	{
		if (ft_memcmp(head->command, cmd, ft_strlen(cmd)) == 0)
		{
			if (cmd && ft_memcmp(cmd, "pwd", ft_strlen(cmd)) == 0)
			{
				ft_pwd(big_struct, head);
				return (1);
			}
			else if (cmd && ft_memcmp(cmd, "echo", 4) == 0)
			{
				ft_echo(big_struct, head);
				return (1);
			}
			//else if (les prochains builtins :D )
		}
		head = head->next;
	}
	return (0);
}

void	ft_exec(t_big_struct *big_struct)
{
	t_cmd_lst	*head;
	t_cmd_lst	*head_tmp;

	head = big_struct->cmd_lst;
	head_tmp = big_struct->cmd_lst;
	while (head_tmp && head_tmp->command)
	{
		printf("\thead of exec =%s\n", head_tmp->command);
		head_tmp = head_tmp->next;
	}
	if (head->command && ft_strnstr_exec(head->command, "<<", ft_strlen(head->command)))
		ft_heredoc(big_struct);
	if (head && !head->next)
	{
		if (ft_check_builtin(big_struct, head->command))
			return ;
		else
			ft_simple_exec(big_struct, head);
		wait(NULL);
	}
	else if (head && head->next)
	{
		ft_multi_pipe(big_struct);
	}
}
