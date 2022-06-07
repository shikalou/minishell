/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:22:19 by ldinaut           #+#    #+#             */
/*   Updated: 2022/06/07 14:04:08 by mcouppe          ###   ########.fr       */
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
		if (ft_strnstr_heredoc(head->command, "<<", ft_strlen(head->command), i))
		{
			while (get_next_heredoc(head->command,"<<", i) > 0)
			{
				printf("strnstr = %s\n ", ft_strnstr_heredoc(head->command, "<<", ft_strlen(head->command), i));
				i = (get_next_heredoc(head->command, "<<", i));
			}
		}
		i = 0;
		head = head->next;
	}
}

void	ft_exec(t_big_struct *big_struct)
{
	t_cmd_lst *head;
	t_cmd_lst	*head_tmp;
//	char	**tab_split;

	head = big_struct->cmd_lst;
	head_tmp = big_struct->cmd_lst;
	while (head_tmp)
	{
		printf("%s\n", head_tmp->command);
		head_tmp = head_tmp->next;
	}
	// j'ai eu besoin de faire des strnstr exec pour add un split des quotes dans le strnstr
	if (ft_strnstr_exec(head->command, "<<", ft_strlen(head->command)))
		ft_heredoc(big_struct);
	while (head)
	{
	//	if (head->next)
	//		big_struct->pipefd = pipe();
		if (ft_strnstr_exec(head->command, "pwd", ft_strlen(head->command)))
			ft_pwd(big_struct);
		head = head->next;
	}
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
