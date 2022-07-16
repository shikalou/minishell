/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtrim_aug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:53:29 by mcouppe           #+#    #+#             */
/*   Updated: 2022/07/16 20:09:57 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strtrim_size(char *cmd)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!cmd)
		return (i);
	while (cmd && cmd[i++] != '\0')
	{
		if (cmd[i] == '"')
		{
			j += 2;
			i++;
			while (cmd[i] && cmd[i] != '"')
				i++;
		}
		else if (cmd[i] == '\'')
		{
			j += 2;
			i++;
			while (cmd[i] && cmd[i] != '\'')
				i++;
		}
	}
	return (i - j);
}

char	*strtrim_aug(char *cmd)
{
	char	*new_cmd;
	int		i;
	int		j;
	int		size;

	size = strtrim_size(cmd);
	i = -1;
	j = 0;
	if (ft_strnstr(cmd, "export ", 7) != NULL)
		return (cmd);
	new_cmd = malloc(sizeof(char) * size + 1);
	if (!new_cmd)
		return (NULL);
	while (cmd && cmd[++i])
	{
		if (cmd[i] == '"')
		{
			i++;
			while (cmd[i] && cmd[i] != '"')
				new_cmd[j++] = cmd[i++];
		}
		else if (cmd[i] == '\'')
		{
			i++;
			while (cmd[i] && cmd[i] != '\'')
				new_cmd[j++] = cmd[i++];
		}
		else
			new_cmd[j++] = cmd[i];
	}
	new_cmd[j] = '\0';
	if (cmd)
		free(cmd);
	return (new_cmd);
}
