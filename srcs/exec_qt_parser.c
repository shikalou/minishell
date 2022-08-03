/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_qt_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 16:17:41 by mcouppe           #+#    #+#             */
/*   Updated: 2022/08/03 19:02:47 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_sz_pre_spacer(char *old, int i)
{
	int		j;
	int		check;

	check = 0;
	while (old && old[i])
	{
		j = i + 1;
		if (old[i] == '"' && old[j] && old[j] == '"' && old[j + 1]
			&& old[j + 1] != ' ' && old[j + 2] && old[j + 2] != '"')
		{
			check++;
			i += 2;
		}
		else if (old[i] == '\'' && old[j] && old[j] == '\'' && old[j + 1]
			&& old[j + 1] != ' ' && old[j + 2] && old[j + 2] != '\'')
		{
			check++;
			i += 2;
		}
		else
			i++;
	}
	return (i + check);
}

char	*qt_pre_spacer(char *old, int i, int j)
{
	size_t	size;
	int	check;
	char	*result;

	check = 0;
	size = get_sz_pre_spacer(old, 0);
	if (!old || size == ft_strlen(old))
		return (old);
	result = malloc(sizeof(char) * size + 1);
	if (!result)
		return (NULL);
	while (old && old[i])
	{
		if (old[i + 1] && old[i + 2] && ((old[i] == '"' && old[i + 1] == '"'
					&& old[i + 2] != ' ') || (old[i] == '\''
					&& old[i + 1] == '\'' && old[i + 2] != ' '))
					&& check == 1)
		{
			result[j++] = old[i++];
			result[j++] = old[i++];
			result[j++] = ' ';
		}
		else if (old[i + 1] && old[i + 2] && ((old[i] == '"' && old[i + 1] == '"' && old[i + 2] == ' ')
					|| (old[i] == '\'' && old[i + 1] == '\'' && old[i + 2] == ' '))
					&& check == 0)
		{
			result[j++] = old[i++];
			result[j++] = old[i++];
			check++;
		}
		else
			result[j++] = old[i++];
	}
	result[j] = '\0';
	free(old);
	return (result);
}

char	*qt_aft_spacer(char *old, int i, int j)
{
	size_t	size;
	char	*result;

	size = get_sz_aft_spacer(old, 0);
	if (!old || size == ft_strlen(old))
		return (old);
	result = malloc(sizeof(char) * size + 1);
	if (!result)
		return (NULL);
	while (old && old[i])
	{
		if ((i > 0) && old[i + 1] && ((old[i] == '"' && old[i - 1] != ' '
					&& old[i + 1] == '"') || (old[i] == '\''
					&& old[i - 1] != ' ' && old[i + 1] == '\'')))
		{
			result[j++] = ' ';
			result[j++] = old[i++];
			result[j++] = old[i++];
		}
		else
			result[j++] = old[i++];
	}
	result[j] = '\0';
	free(old);
	return (result);
}

int	get_sz_aft_spacer(char *old, int i)
{
	int	j;
	int	check;

	check = 0;
	while (old && old[i])
	{
		j = i + 1;
		if ((i > 0) && old[i] == '"' && old[j] && old[j] == '"'
			&& old[i - 1] != ' ')
		{
			check++;
			i += 2;
		}
		else if ((i > 0) && old[i] == '\'' && old[j] && old[j] == '\''
			&& old[i - 1] != ' ')
		{
			check++;
			i += 2;
		}
		else
			i++;
	}
	return (i + check);
}
