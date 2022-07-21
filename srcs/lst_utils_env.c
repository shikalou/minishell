/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:19:31 by ldinaut           #+#    #+#             */
/*   Updated: 2022/07/21 19:58:56 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_lst	*ft_lstnew_env(int i, char *env_line)
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

void	ft_lstclear_env(t_env_lst *env_lst)
{
	t_env_lst	*lst_tmp;

	lst_tmp = env_lst;
	if (!env_lst)
		return ;
	while (env_lst)
	{
		lst_tmp = env_lst->next;
		if (ft_strlen(env_lst->line) > 0)
			free(env_lst->line);
		free(env_lst);
		env_lst = lst_tmp;
	}
	free(env_lst);
}

int	ft_lstsize_env(t_env_lst *lst)
{
	int		i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
