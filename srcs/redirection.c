/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:10:29 by ldinaut           #+#    #+#             */
/*   Updated: 2022/08/05 14:02:30 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*update_flux(t_big *b, int size, int index)
{
	int		i;
	char	*new_cmd;

	i = 0;
	new_cmd = malloc(sizeof(char) * size + 1);
	if (!new_cmd)
		return (NULL);
	new_cmd[0] = '\0';
	while (b->spaced_par && b->spaced_par[i])
	{
		if (i == index || i == index + 1)
		{
			free(b->spaced_par[i]);
			b->spaced_par[i] = ft_strdup(" ");
		}
		else
		{
			ft_strlcat(new_cmd, b->spaced_par[i], size);
			ft_strlcat(new_cmd, " ", size);
		}
		i++;
	}
	return (new_cmd);
}

void	redirect_out(t_big *b, t_cmd_lst *cmd_lst, int i, int j)
{
	int	k;

	i++;
	update_spaced_par(b->spaced_par[i], b, i);
	if (cmd_lst->fd_out != 1)
		close(cmd_lst->fd_out);
	if (j == 1)
		cmd_lst->fd_out = open(b->spaced_par[i],
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		cmd_lst->fd_out = open(b->spaced_par[i],
				O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (cmd_lst->fd_out == -1)
	{
		b->status = 1;
		printf("%s : %s\n", strerror(errno), b->spaced_par[i + 1]);
	}
	k = ft_strlen(cmd_lst->command);
	free(cmd_lst->command);
	cmd_lst->command = update_flux(b, k, i - 1);
}

void	redirect_in(t_big *b, t_cmd_lst *cmd_lst, int i)
{
	int	k;

	i++;
	update_spaced_par(b->spaced_par[i], b, i);
	if (cmd_lst->fd_in == -1)
	{
		k = ft_strlen(cmd_lst->command);
		free(cmd_lst->command);
		cmd_lst->command = update_flux(b, k, i - 1);
		return ;
	}
	if (cmd_lst->fd_in != 0)
		close(cmd_lst->fd_in);
	cmd_lst->fd_in = open(b->spaced_par[i], O_RDONLY, 0644);
	if (cmd_lst->fd_in == -1)
	{
		b->status = 1;
		printf("%s : %s\n", strerror(errno), b->spaced_par[i]);
		cmd_lst->fd_in = -1;
	}
	k = ft_strlen(cmd_lst->command);
	free(cmd_lst->command);
	cmd_lst->command = update_flux(b, k, i - 1);
}

void	redirect_heredoc(t_big *b, t_cmd_lst *cmd_lst, int i)
{
	int	k;

	ft_heredoc_main(b, cmd_lst, i + 1);
	if (b->cmd_lst != NULL)
	{
		k = ft_strlen(cmd_lst->command);
		free(cmd_lst->command);
		cmd_lst->command = update_flux(b, k, i);
	}
	else
		cmd_lst = NULL;
}

void	parsing_redirection(t_big *big_struct, int i)
{
	t_cmd_lst	*cmd_lst;

	cmd_lst = big_struct->cmd_lst;
	while (cmd_lst != NULL)
	{
		i = -1;
		big_struct->spaced_par = ft_sdf(cmd_lst->command, ' ');
		while (big_struct->spaced_par && big_struct->spaced_par[++i])
		{
			if (ft_strcmp(big_struct->spaced_par[i], "<") == 0)
				redirect_in(big_struct, cmd_lst, i);
			else if (ft_strcmp(big_struct->spaced_par[i], "<<") == 0)
				redirect_heredoc(big_struct, cmd_lst, i);
			else if (ft_strcmp(big_struct->spaced_par[i], ">") == 0)
				redirect_out(big_struct, cmd_lst, i, 1);
			else if (ft_strcmp(big_struct->spaced_par[i], ">>") == 0)
				redirect_out(big_struct, cmd_lst, i, 0);
		}
		ft_free_tab(big_struct->spaced_par);
		big_struct->spaced_par = NULL;
		if (big_struct->cmd_lst != NULL)
			cmd_lst = cmd_lst->next;
		else
			break ;
	}
}
