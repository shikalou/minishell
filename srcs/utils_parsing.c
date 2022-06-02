/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:46:20 by mcouppe           #+#    #+#             */
/*   Updated: 2022/06/02 13:06:45 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	charisalphaorspace(char c)
{
	if (!c)
		return (0);
	if (((c >= 32 && c < 60) || c == 61 || (c > 62 && c < 127)))
		return (1);
	else
		return (0);
}

int	charisalpha_aug(char *cmd, int index, int end)
{
	index++;
	while (index < end)
	{
		if (cmd[index] != ' ')
			return (0);
		else
			index++;
	}
	return (1);
}

int	charisalpha(char c)
{
	if (!c)
		return (0);
	if (c >= 33 && c < 127)
		return (1);
	else
		return (0);
}

char	*add_space(char *cmd, int index)
{
	char		*new;
	int			i;
	int			j;

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
			j += 2;
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
			new[++j] = cmd[i];
			new[++j] = cmd[++i];
			new[++j] = ' ';
		}
		else
			new[j] = cmd[i];
		j++;
	}
	new[j] = '\0';
	free(cmd);
	return (new);
}
