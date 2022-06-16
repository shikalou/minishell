/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test-redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:10:29 by ldinaut           #+#    #+#             */
/*   Updated: 2022/06/16 16:16:28 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*update_flux(char **spaced, char *flux, int size)
{
	int		i;
	char	*new_cmd;

	i = 0;
	new_cmd = malloc(sizeof(char) * size + 1);
	while (spaced && spaced[i])
	{
		printf("coucou 1\n");
		if (ft_memcmp(spaced[i], flux, ft_strlen(spaced[i])) == 0)
		{
			printf("coucou 1 BIS\n");
			i++;
		}
		else
		{
			printf("on est dans strlcat\n");
			ft_strlcat(new_cmd, spaced[i], size);
			ft_strlcat(new_cmd, " ", size);
		}
		i++;
	}
	return (new_cmd);
}

void	parsing_redirection(t_big_struct *big_struct)
{
	t_cmd_lst	*cmd_lst;
	char		**spaced;
	int			i;
	int			k;

	cmd_lst = big_struct->cmd_lst;
	while (cmd_lst)
	{
		i = 0;
		spaced = ft_split(cmd_lst->command, ' ');
		while (spaced && spaced[i])
		{
			printf("coucou 2\n");
			if (ft_memcmp(spaced[i], "<", ft_strlen(spaced[i])) == 0)
			{
				i++;
				cmd_lst->fd_in = open(spaced[i], O_RDONLY);
				if (cmd_lst->fd_in == -1)
					printf("%s : %s\n", strerror(errno), spaced[i + 1]);
				printf("coucou 3\n");
				k = ft_strlen(cmd_lst->command);
				free(cmd_lst->command);
				cmd_lst->command = update_flux(spaced, "<", k);
			}
			else if (ft_memcmp(spaced[i], ">", ft_strlen(spaced[i])) == 0)
			{
				i++;
				cmd_lst->fd_out = open(spaced[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
				if (cmd_lst->fd_out == -1)
					printf("%s : %s\n", strerror(errno), spaced[i + 1]);
				printf("FD OUT DANS PARSING%d\n", cmd_lst->fd_out);
				k = ft_strlen(cmd_lst->command);
				free(cmd_lst->command);
				cmd_lst->command = update_flux(spaced, ">", k);
			}
			i++;
		}
		ft_free_tab(spaced);
		cmd_lst = cmd_lst->next;
	}
	printf("coucou 4\n");
}
