/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 21:38:46 by mcouppe           #+#    #+#             */
/*   Updated: 2022/08/02 16:31:02 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_lstclear_cmd(t_cmd_lst *cmd_lst)
{
	t_cmd_lst	*lst_tmp;

	lst_tmp = cmd_lst;
	if (!cmd_lst)
		return ;
	while (cmd_lst != NULL)
	{
		if (cmd_lst->fd_in != 0 && cmd_lst->fd_in != -1)
			close(cmd_lst->fd_in);
		if (cmd_lst->fd_out != 1)
			close(cmd_lst->fd_out);
		lst_tmp = cmd_lst->next;
		free(cmd_lst->command);
		free(cmd_lst);
		cmd_lst = lst_tmp;
	}
	free(cmd_lst);
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
