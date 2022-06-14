/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:22:19 by ldinaut           #+#    #+#             */
/*   Updated: 2022/06/14 13:51:36 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_big_struct *big_struct)
{
	printf("%s\n", big_struct->absolut_path);
}

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
void	ft_exec_pipe(t_big_struct *big_struct)
{
	t_cmd_lst	*head;
	int			pid;
	int			i;

	head = big_struct->cmd_lst;
	big_struct->spaced_cmd = ft_split(head->command, ' ');
	i = 0;
	while (big_struct->spaced_cmd[i] != NULL)
	{
		printf("space_cmd[%d] = %s\n", i, big_struct->spaced_cmd[i]);
		i++;
	}
	//pipe(big_struct->pipefd);
	pid = fork();
	if (pid == 0)
	{
		if (ft_find_check_path(big_struct, big_struct->spaced_cmd) != NULL)
		{
			printf("hihi\n");
			execve(big_struct->cmd_updated, big_struct->spaced_cmd, big_struct->envp);
			perror("execve");
			printf("apres le execve ?????\n");
		}
	}
}

void	ft_exec(t_big_struct *big_struct)
{
	t_cmd_lst	*head;
	t_cmd_lst	*head_tmp;
	//char		**spaced_cmd;

	head = big_struct->cmd_lst;
	head_tmp = big_struct->cmd_lst;
	while (head_tmp && head_tmp->command)
	{
		printf("%s\n", head_tmp->command);
		head_tmp = head_tmp->next;
	}
	if (head->command && ft_strnstr_exec(head->command, "<<", ft_strlen(head->command)))
		ft_heredoc(big_struct);
	if (head/* && head->next*/)
	{
		ft_exec_pipe(big_struct);
		wait(NULL);
	}
	else
	{
		while (head && head->command)
		{
		//	spaced_cmd = ft_split(head->command, ' ');
	//		big_struct->pipefd = pipe();
			if (head->command && ft_memcmp(head->command, "pwd", ft_strlen(head->command)) == 0)
				ft_pwd(big_struct);
			else if (head->command && ft_memcmp(head->command, "echo", 4) == 0)
				printf("echoooooo lol\n");
	//		ft_free_spaced(spaced_cmd);
			head = head->next;
		}
	}
	printf("on sort ou pas ?\n");
}

/*
	ft echo(stuct)
{
	if head->next NULL
		exec simple
	else
	{
		exec avec pipe
	}
}
*/
