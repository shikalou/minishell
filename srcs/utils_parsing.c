/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:46:20 by mcouppe           #+#    #+#             */
/*   Updated: 2022/05/25 16:37:51 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	charisalphaorspace(char c)
{
	if ((c >= '0' && c <= '9') || c == ' ' || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}

int	charisalpha(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
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
	if (index != 0)
		new = malloc(sizeof(char) * (ft_strlen(cmd) + 2 + 1));
	else
		new = malloc(sizeof(char) * (ft_strlen(cmd) + 1 + 1));
	if (!new)
		return (NULL);
	while (cmd[++i])
	{
		if (index == 0 && i == index)
		{
			new[j] = cmd[i];
			j++;
			new[j] = ' ';
		}
		else if (index != 0 && i == index)
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
	if (index != 0)
		new = malloc(sizeof(char) * (ft_strlen(cmd) + 2 +1));
	else
		new = malloc(sizeof(char) * (ft_strlen(cmd) + 1 + 1));
	if (!new)
		return (NULL);
	while(cmd[++i])
	{
		if (index == 0 && i == index)
		{
			new[j] = cmd[i];
			new[j + 1] = cmd[i + 1];
			new[j + 2] = ' ';
			j += 2;
			i++;
		}
		else if (index != 0 && i == index)
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
