/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:11:18 by ldinaut           #+#    #+#             */
/*   Updated: 2022/06/24 16:02:15 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_between(t_big_struct *big_struct)
{
	if (big_struct->cmd_lst)
	{
		ft_lstclear_cmd(big_struct->cmd_lst);
		big_struct->cmd_lst = NULL;
	}
	if (big_struct->input)
	{
		ft_free_tab(big_struct->input);
		big_struct->input = NULL;
	}
	if (big_struct->spaced_cmd != NULL)
	{
		ft_free_tab(big_struct->spaced_cmd);
		big_struct->spaced_cmd = NULL;
	}
	if (big_struct->spaced_par)
	{
		ft_free_tab(big_struct->spaced_par);
		big_struct->spaced_par = NULL;
	}
	if (big_struct->cmd_updated)
	{
		free(big_struct->cmd_updated);
		big_struct->cmd_updated = NULL;
	}
}

void	ft_free_child(t_big_struct *big_struct)
{
	if (big_struct->absolut_path)
		free(big_struct->absolut_path);
	if (big_struct->spaced_par)
		ft_free_tab(big_struct->spaced_par);
	if (big_struct->input)
		ft_free_tab(big_struct->input);
	ft_free_tab(big_struct->path);
	ft_lstclear_cmd(big_struct->cmd_lst);
	ft_lstclear_env(big_struct->env_lst);
	free(big_struct);
}