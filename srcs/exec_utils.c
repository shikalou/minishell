/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:02:50 by mcouppe           #+#    #+#             */
/*   Updated: 2022/08/04 22:27:53 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_check_slash(t_big *big_s)
{
	if (access(big_s->spaced_cmd[0], X_OK) == 0)
	{
		big_s->cmd_updated = ft_strdup(big_s->spaced_cmd[0]);
		return (big_s->cmd_updated);
	}
	printf("%s: %s\n", strerror(errno), big_s->spaced_cmd[0]);
	return (NULL);
}

char	*ft_find_check_path(t_big *b, char **spaced_cmd, int i)
{
	char	*temp;
	char	**new_path;

	if (ft_strchr(b->spaced_cmd[0], '/'))
		return (ft_check_slash(b));
	new_path = ft_recover_path(b->envp);
	while (new_path && new_path[++i] != NULL)
	{
		temp = ft_strjoin(new_path[i], "/");
		b->cmd_updated = ft_strjoin(temp, spaced_cmd[0]);
		free(temp);
		if (b->cmd_updated && access(b->cmd_updated, X_OK) == 0
			&& open(b->cmd_updated, __O_DIRECTORY) == -1)
		{
			ft_free_tab(new_path);
			return (b->cmd_updated);
		}
		free(b->cmd_updated);
		b->cmd_updated = NULL;
	}
	printf("%s : command not found\n", b->spaced_cmd[0]);
	ft_free_tab(new_path);
	return (NULL);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] == s2[i])
		{
			i++;
		}
		else
			return (s1[i] - s2[i]);
	}
	return (0);
}

void	ft_close_fdinout(t_cmd_lst *cmd_lst)
{
	if (cmd_lst->fd_in != 0)
		close(cmd_lst->fd_in);
	if (cmd_lst->fd_out != 1)
	{
		if (cmd_lst->next && cmd_lst->next->fd_out != cmd_lst->fd_out)
			return ;
		close(cmd_lst->fd_out);
	}
}

void	ft_dup(t_cmd_lst *cmd_lst)
{
	dup2(cmd_lst->fd_in, 0);
	dup2(cmd_lst->fd_out, 1);
}
