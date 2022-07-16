/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:55:04 by mcouppe           #+#    #+#             */
/*   Updated: 2022/07/16 18:52:19 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_str(char **result, char *var, char c)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	j = 0;
	k = 0;
	while (var && var[++i])
	{
		if (var[i] == c)
		{
			result[j][k] = '\0';
			j++;
			k = 0;
		}
		else
			result[j][k++] = var[i];
	}
	result[j][k] = '\0';
	if (j == 0)
	{
		free(result[1]);
		result[1] = NULL;
	}
	result[2] = NULL;
}

char	**se_clean(char **result, int check)
{
	if (check == 1)
		free(result[0]);
	free(result);
	return (NULL);
}

char	**ft_split_export(char *var, char c)
{
	int		i;
	int		j;
	char	**result;

	i = 0;
	j = 0;
	result = malloc(sizeof(char *) * (2 + 1));
	if (!result)
		return (NULL);
	while (var && var[i] && var[i] != c)
		i++;
	result[0] = malloc(1 * (i + 1));
	if (!result[0])
		return (se_clean(result, 0));
	while (var[i] == c)
		i++;
	while (var && var[i] && var[i++] != c)
		j++;
	result[1] = malloc(1 * (j + 1));
	if (!result[1])
		return (se_clean(result, 1));
	fill_str(result, var, c);
	return (result);
}
