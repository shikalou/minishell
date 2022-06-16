/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test-redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:10:29 by ldinaut           #+#    #+#             */
/*   Updated: 2022/06/16 18:43:02 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*update_flux(t_big_struct *b, char *flux, int size, int index)
{
	int		i;
	char	*new_cmd;

	i = 0;
	new_cmd = malloc(sizeof(char) * size + 1);
	new_cmd[0] = '\0';
	while (b->spaced_par && b->spaced_par[i])
	{
		if (ft_memcmp(b->spaced_par[i], flux, ft_strlen(b->spaced_par[i])) == 0 || i == index)
		{
			free(b->spaced_par[i]);
			b->spaced_par[i] = ft_strdup("\0");
			i++;
			free(b->spaced_par[i]);
			b->spaced_par[i] = ft_strdup("\0");
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

void	parsing_redirection(t_big_struct *big_struct)
{
	t_cmd_lst	*cmd_lst;
	int			i;
	int			k;

	cmd_lst = big_struct->cmd_lst;
	while (cmd_lst)
	{
		i = 0;
		big_struct->spaced_par = ft_split(cmd_lst->command, ' ');
		while (big_struct->spaced_par && big_struct->spaced_par[i])
		{
			if (ft_memcmp(big_struct->spaced_par[i], "<", ft_strlen(big_struct->spaced_par[i])) == 0)
			{
				i++;
				cmd_lst->fd_in = open(big_struct->spaced_par[i], O_RDONLY);
				if (cmd_lst->fd_in == -1)
					printf("%s : %s\n", strerror(errno), big_struct->spaced_par[i + 1]);
				k = ft_strlen(cmd_lst->command);
				free(cmd_lst->command);
				cmd_lst->command = update_flux(big_struct, "<", k, i - 1);
			}
			else if (ft_memcmp(big_struct->spaced_par[i], ">", ft_strlen(big_struct->spaced_par[i])) == 0)
			{
				i++;
				cmd_lst->fd_out = open(big_struct->spaced_par[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
				if (cmd_lst->fd_out == -1)
					printf("%s : %s\n", strerror(errno), big_struct->spaced_par[i + 1]);
				k = ft_strlen(cmd_lst->command);
				free(cmd_lst->command);
				cmd_lst->command = update_flux(big_struct, "<", k, i - 1);
			}
			i++;
		}
		cmd_lst = cmd_lst->next;
	}
}