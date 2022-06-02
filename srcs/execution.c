/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:22:19 by ldinaut           #+#    #+#             */
/*   Updated: 2022/06/02 15:41:38 by mcouppe          ###   ########.fr       */
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
	printf("strnstr = %s\n ", ft_strnstr_heredoc(head->command, "<<", ft_strlen(head->command), i));
}

void	ft_exec(t_big_struct *big_struct)
{
	t_cmd_lst *head;

	head = big_struct->cmd_lst;
	if (ft_strnstr_exec(head->command, "<<", ft_strlen(head->command)))
	{
		ft_heredoc(big_struct);
	}
	if (ft_strnstr_exec(head->command, "pwd", ft_strlen(head->command)))
		ft_pwd(big_struct);
}
