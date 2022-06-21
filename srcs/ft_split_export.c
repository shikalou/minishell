/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <mcouppe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 20:17:01 by mcouppe           #+#    #+#             */
/*   Updated: 2022/06/22 00:50:50 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_export_size(char *cmd, int i)
{
	int	k;

//	on skip habilement les espaces
	while (cmd && cmd[i] && cmd[i] == ' ')
		i++;
	k = i;
//	on test s'il y a qque chose apres les espaces :
	if (cmd && cmd[i] != '\0')
	{
		k = i;
		while (cmd && cmd[i] && cmd[i] != ' ')
		{
			if (cmd[i] == '"')
			{
				i++;
				while (cmd[i] && cmd[i] != '"')
					i++;
				i++;
				return (i - k);
			}
			i++;
		}
	}
	return (i - k);
}

void	split_fill_first(char *cmd, char **result, int fst_size)
{
	int 		i;
	int		j;

	i = 0;
	j = 0;
	while (cmd && cmd[i])
	{
		if (cmd[i] == ' ')
			i++;
		else
		{
			while (cmd && cmd[i] && cmd[i] != ' ')
				result[0][j++] = cmd[i++];
			result[0][fst_size] = '\0';
			return ;
		}
		i++;
	}
}

void	split_fill_second(char *cmd, char **result, int snd_size, int index)
{
	int		i;
	int		j;
	int		k;

	i = index;
	k = 0;
	while (cmd && cmd[i] && cmd[i] == ' ')
		i++;
	if (cmd[i] == '\0')
	{
		result[1] = NULL;
		return ;
	}
	else
	{
		j = i + snd_size;
		while (cmd[i] && i < j)
			result[1][k++] = cmd[i++];
	}
	result[1][snd_size] = '\0';
}

char	**ft_split_export(char *cmd)
{
	int		i;
	int		j;
	int		k;
	char	**result;

	i = 0;
	j = 0;
	k = 0;
	if (!cmd || cmd[i] == '\0')
		return (NULL);
/*
	FIRST SIZE split[0] == "export"
*/
	if (cmd[i] == ' ')
	{
		while (cmd[i] && cmd[i] == ' ')
			i++;
	}
	while (cmd && cmd[i] && cmd[i] != '\0' && cmd[i] != ' ')
	{
		i++;
		j++;
	}
	if (cmd[i] == ' ')
	{
//			k nous permet de compter les char
//			genre ds export LOL="mdr" k vaudra size de LOL="mdr"
// 	C'est la SECOND SIZE split[1] = LOL="mdr"
		k = split_export_size(cmd, i);
		printf("k == %d\n", k);
	}
	result = malloc(sizeof(char *) * 2 + 1);
	if (!result)
		return (NULL);
	result[0] = malloc(sizeof(char) * j + 1);
	if (!result[0])
	{
		free(result);
		return (NULL);
	}
	result[1] = malloc(sizeof(char) * k + 1);
	if (!result[1])
	{
		free(result[0]);
		free(result);
		return (NULL);
	}
	result[2] = NULL;
	split_fill_first(cmd, result, j);
	split_fill_second(cmd, result, k, i);
	return (result);
}
