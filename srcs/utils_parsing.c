/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:46:20 by mcouppe           #+#    #+#             */
/*   Updated: 2022/05/31 14:52:42 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	charisalphaorspace(char c)
{
	if (!c)
		return (0);
	if ((c >= '0' && c <= '9') || c == ' ' || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}

int	charisalpha(char c)
{
	if (!c)
		return (0);
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == '"'))
		return (1);
	else
		return (0);
}

char	*add_space(char *cmd, int index)
{
	char		*new;
	int		i;
	int		j;

	i = -1;
	j = 0;
	new = malloc(sizeof(char) * (ft_strlen(cmd) + 2 + 1));
	if (!new)
		return (NULL);
	while (cmd[++i])
	{
		if (i == index)
		{
			new[j] = ' ';
			new[j + 1] = cmd[i];
			new[j + 2] = ' ';
			j+= 2;
		}
		else
			new[j] = cmd[i];
		j++;
	}
	new[j] = '\0';
	free(cmd);
	return (new);
}

char	*add_space_hereapp(char *cmd, int index)
{
	char	*new;
	int	i;
	int	j;

	i = -1;
	j = 0;
	new = malloc(sizeof(char) * (ft_strlen(cmd) + 2 +1));
	if (!new)
		return (NULL);
	while(cmd[++i])
	{
		if (i == index)
		{
			new[j] = ' ';
			new[j + 1] = cmd[i];
			new[j + 2] = cmd[i + 1];
			new[j + 3] = ' ';
			j += 3;
			i++;
		}
		else
			new[j] = cmd[i];
		j++;
	}
	new[j] = '\0';
	free(cmd);
	return (new);
}
