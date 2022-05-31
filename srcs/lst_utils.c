/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:19:31 by ldinaut           #+#    #+#             */
/*   Updated: 2022/05/31 16:59:59 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_lst	*ft_lstnew_cmd(int i, char *cmd)
{
	t_cmd_lst	*newlist;

	newlist = malloc(sizeof(t_cmd_lst));
	if (!newlist)
		return (NULL);
	newlist->next = NULL;
	newlist->index = i;
	newlist->command = cmd;
	return (newlist);
}

t_env_lst	*ft_lstnew_env(int	i, char *env_line)
{
	t_env_lst	*newlist;

	newlist = malloc(sizeof(t_env_lst));
	if (!newlist)
		return (NULL);
	newlist->next = NULL;
	newlist->index = i;
	newlist->line = env_line;
	return (newlist);
}

void	ft_lstadd_back_cmd(t_cmd_lst **alst, t_cmd_lst *new)
{
	t_cmd_lst	*temp;

	temp = *alst;
	if (!(*alst))
		*alst = new;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

void	ft_lstadd_back_env(t_env_lst **alst, t_env_lst *new)
{
	t_env_lst	*temp;

	temp = *alst;
	if (!(*alst))
		*alst = new;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}