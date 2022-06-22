/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:19:31 by ldinaut           #+#    #+#             */
/*   Updated: 2022/06/22 17:19:57 by mcouppe          ###   ########.fr       */
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
	newlist->fd_in = 0;
	newlist->fd_out = 1;
	newlist->command = cmd;
	return (newlist);
}

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

void	ft_lstclear_env(t_env_lst *env_lst)
{
	t_env_lst	*lst_tmp;

	lst_tmp = env_lst;
	if (!env_lst)
		return ;
	while (env_lst != NULL)
	{
		lst_tmp = env_lst->next;
		free(env_lst);
		env_lst = lst_tmp;
	}
	free(env_lst);
}

void	ft_lstclear_cmd(t_cmd_lst *cmd_lst)
{
	t_cmd_lst	*lst_tmp;

	lst_tmp = cmd_lst;
	if (!cmd_lst)
		return ;
	while (cmd_lst != NULL)
	{
		lst_tmp = cmd_lst->next;
		if(cmd_lst->command)
			free(cmd_lst->command);
		free(cmd_lst);
		cmd_lst = lst_tmp;
	}
	free(cmd_lst);
}

int	ft_lstsize_cmd(t_cmd_lst *lst)
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

/*
void	ft_lstclear(t_list **lst)
{
	t_list	*lst_tmp;

	lst_tmp = (*lst);
	if (!lst)
		return ;
	while ((*lst) != NULL)
	{
		lst_tmp = (*lst)->next;
		free(*lst);
		(*lst) = lst_tmp;
	}
	free(lst);
}*/
