/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:22:19 by ldinaut           #+#    #+#             */
/*   Updated: 2022/06/15 13:39:58 by ldinaut          ###   ########.fr       */
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

int	ft_simple_exec(t_big_struct *big_struct)
{
	int			pid;
	int			i;

	i = 0;
	while (big_struct->spaced_cmd[i] != NULL)
	{
		printf("space_cmd[%d] = %s\n", i, big_struct->spaced_cmd[i]);
		i++;
	}
	pid = fork();
	if (pid == 0)
	{
		if (ft_find_check_path(big_struct, big_struct->spaced_cmd) != NULL)
		{
		//	dup2(big_struct->cmd_lst->fd_in, 0);
			execve(big_struct->cmd_updated, big_struct->spaced_cmd, big_struct->envp);
		//	dup2(big_struct->cmd_lst->fd_out, 1);
			perror("execve");
		}
		exit(1);
	}
	return (0);
}

int	ft_check_builtin(t_big_struct *big_struct)
{
	t_cmd_lst *head;

	head = big_struct->cmd_lst;
	while (head && head->command)
		{
			if (head->command && ft_memcmp(head->command, "pwd", ft_strlen(head->command)) == 0)
			{
				ft_pwd(big_struct, head);
				return (1);
			}
			else if (head->command && ft_memcmp(head->command, "echo", 4) == 0)
			{
				ft_echo(big_struct, head->command);
				return (1);
			}
			//else if (les prochains builtins :D )
			head = head->next;
		}
		return (0);
}

void	ft_multi_pipe(t_big_struct *big_struct)
{
	t_cmd_lst	*head;
	//int			n_cmd;

	head = big_struct->cmd_lst;
	//n_cmd = ft_lstsize(cmd_lst);
	if (big_struct->spaced_cmd != NULL)
		free(big_struct->spaced_cmd);
	big_struct->spaced_cmd = ft_split(head->command, ' ');
	// commande simple
	if (ft_check_builtin(big_struct))
			;
	else
			ft_simple_exec(big_struct);
	head = head->next;
	while (head->next)
	{
		if (big_struct->spaced_cmd != NULL)
			free(big_struct->spaced_cmd);
		big_struct->spaced_cmd = ft_split(head->command, ' ');
		// premiere exec (builtin ou non)
		// boucle while sur liste size -2 pour celles du milieu si il y a (pipe dans la fonction avec fd_temp)
		// exec last (pas de pipe du coup)
		head = head->next;
	}
		// if (chck builtin)
		// else if (check exec)
		// 	ft_multi_exec(big_struct);
		// else
		//	command not found
}

void	ft_exec(t_big_struct *big_struct)
{
	t_cmd_lst	*head;
	t_cmd_lst	*head_tmp;

	head = big_struct->cmd_lst;
	head_tmp = big_struct->cmd_lst;
	big_struct->spaced_cmd = ft_split(head->command, ' ');
	while (head_tmp && head_tmp->command)
	{
		printf("%s\n", head_tmp->command);
		head_tmp = head_tmp->next;
	}
	if (head->command && ft_strnstr_exec(head->command, "<<", ft_strlen(head->command)))
		ft_heredoc(big_struct);
	if (head && !head->next)
	{
		if (ft_check_builtin(big_struct))
			return ;
		else
			ft_simple_exec(big_struct);
		wait(NULL);
	}
	else if (head && head->next)
	{
		ft_multi_pipe(big_struct);
	}
}
