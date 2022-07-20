/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtrim_aug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:53:29 by mcouppe           #+#    #+#             */
/*   Updated: 2022/07/20 22:48:20 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strtrim_size(char *cmd, int check)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	if (!cmd)
		return (i);
	while (cmd && cmd[i++] != '\0')
	{
		if (cmd[i] == '"')
		{
			k = 0;
			j += 2;
			i++;
			if (cmd[i] == '"' && check == 1)
			{
				j -= 2;
				i++;
			}
			else if (cmd[i] == ' ')
			{
				while (cmd[i] && cmd[i] == ' ' && cmd[i++] != '"')
					k++;
				if (cmd[i] == '"')
				{
					i -= k;
					i++;
					j -= 2;
				}
				else
					i -= k;
				while (cmd[i] && cmd[i] != '"')
					i++;
			}
			else
			{
				while (cmd[i] && cmd[i] != '"')
					i++;
			}
		}
		else if (cmd[i] == '\'')
		{
			j += 2;
			i++;
			if (cmd[i] == '\'')
				j -= 2;
			else if (cmd[i] == ' ')
			{
				while (cmd[i] && cmd[i] == ' ' && cmd[i++] != '\'')
					k++;
				if (cmd[i] == '\'')
				{
					i -= k;
					i++;
					j -= 2;
				}
				else
					i -= k;
			}
			while (cmd[i] && cmd[i] != '\'')
				i++;
		}
	}
	return ((i + 1) - j);
}

void	ft_fill_trim(char *new_cmd, char *cmd, int check)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (cmd && cmd[i])
	{
		if (cmd[i] == '"')
		{
			k = 0;
			i++;
			printf("cmd[%d] = %c<-\n", i, cmd[i]);
			if (cmd[i] == '"' && check == 0)
			{
				new_cmd[j++] = cmd[i];
				new_cmd[j++] = cmd[i++];
			}
			else if (cmd[i] == ' ')
			{
				printf("i first = %d\n", i);
				while (cmd[i] && cmd[i] == ' ' && cmd[i++] != '"')
					k++;
				printf("k = %d\n", k);
				if (cmd[i] == '"')
				{
					new_cmd[j++] = cmd[i];
					new_cmd[j++] = cmd[i];
					i++;
				}
				else
				{
					printf("i second = %d\n", i);
					i -= k;
					printf("i third = %d\n", i);
				}
				while (cmd[i] && cmd[i] != '"')
					new_cmd[j++] = cmd[i++];
			}
			else
			{
				while (cmd[i] && cmd[i] != '"')
					new_cmd[j++] = cmd[i++];
			}
		}
		else if (cmd[i] == '\'')
		{
			i++;
			if (cmd[i] == '\''&& check == 0)
			{
				new_cmd[j++] = cmd[--i];
				new_cmd[j++] = cmd[i++];
			}
			else if (cmd[i] == ' ')
			{
				while (cmd[i] && cmd[i] == ' ' && cmd[i++] != '\'')
					k++;
				if (cmd[i] == '\'')
				{
					new_cmd[j++] = cmd[i];
					new_cmd[j++] = cmd[i];
					i++;
				}
				else
					i -= k;
				while (cmd[i] && cmd[i] != '\'')
					new_cmd[j++] = cmd[i++];
			}
			else
			{
				while (cmd[i] && cmd[i] != '\'')
					new_cmd[j++] = cmd[i++];
			}
		}
		else
			new_cmd[j++] = cmd[i++];
	}
	new_cmd[j] = '\0';
}

char	*strtrim_aug(char *cmd, int check)
{
	char	*new_cmd;
	int		size;

	size = strtrim_size(cmd, check);
	if (ft_strnstr(cmd, "export ", 7) != NULL)
		return (cmd);
	new_cmd = malloc(sizeof(char) * size + 1);
	if (!new_cmd)
		return (NULL);
	ft_fill_trim(new_cmd, cmd, check);
	if (cmd)
		free(cmd);
	return (new_cmd);
}
