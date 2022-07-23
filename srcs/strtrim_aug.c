/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtrim_aug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:53:29 by mcouppe           #+#    #+#             */
/*   Updated: 2022/07/23 21:40:28 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	size_calculator(t_trim *tr)
{
	if (tr->cmd[tr->i] == tr->c && tr->check == 1)
	{
		tr->j -= 2;
		tr->i++;
	}
	else if (tr->cmd[tr->i] == ' ')
	{
		while (tr->cmd[tr->i] && tr->cmd[tr->i] == ' ' 
			&& tr->cmd[tr->i++] != tr->c)
			tr->k++;
		if (tr->cmd[tr->i] == tr->c)
		{
			tr->i -= tr->k;
			tr->i++;
			tr->j -= 2;
		}
		else
			tr->i -= tr->k;
	}
	while (tr->cmd[tr->i] && tr->cmd[tr->i] != '"')
		tr->i++;
}

int	strtrim_size(t_trim *tr)
{
	if (!tr->cmd)
		return (tr->i);
	while (tr->cmd && tr->cmd[tr->i++] != '\0')
	{
		if (tr->cmd[tr->i] == '"')
		{
			tr->k = 0;
			tr->j += 2;
			tr->c = '"';
			tr->i++;
			size_calculator(tr);
		}
		else if (tr->cmd[tr->i] == '\'')
		{
			tr->j += 2;
			tr->k = 0;
			tr->c = '\'';
			tr->i++;
			size_calculator(tr);
		}
	}
	return ((tr->i + 1) - tr->j);
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
			if (cmd[i] == '"' && check == 0)
			{
				new_cmd[j++] = cmd[i];
				new_cmd[j++] = cmd[i++];
				check++;
			}
			else if (cmd[i] == '"' && check != 0)
				i++;
			else if (cmd[i] == ' ')
			{
				while (cmd[i] && cmd[i] == ' ' && cmd[i++] != '"')
					k++;
				if (cmd[i] == '"')
				{
					new_cmd[j++] = cmd[i];
					new_cmd[j++] = cmd[i];
					i++;
				}
				else
					i -= k;
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
			if (cmd[i] == '\'' && check == 0)
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

void	ft_init_trim(t_trim *trim, int check, char *cmd)
{
	trim->i = 0;
	trim->j = 0;
	trim->cmd = cmd;
	trim->check = check;
	trim->k = 0;
	trim->c = '"';
}

char	*strtrim_aug(char *cmd, int check)
{
	t_trim		trim;
	char	*new_cmd;
	int		size;

	ft_init_trim(&trim, check, cmd);
	size = strtrim_size(&trim);
	if (ft_strnstr(cmd, "export ", ft_strlen(cmd)) != NULL)
		return (cmd);
	if (ft_strnstr(cmd, "echo ", ft_strlen(cmd)) != NULL)
		return (cmd);
	new_cmd = malloc(sizeof(char) * size + 1);
	if (!new_cmd)
		return (NULL);
	ft_fill_trim(new_cmd, cmd, check);
	if (cmd)
		free(cmd);
	return (new_cmd);
}
