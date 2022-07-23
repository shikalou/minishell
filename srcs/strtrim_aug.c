/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtrim_aug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:53:29 by mcouppe           #+#    #+#             */
/*   Updated: 2022/07/23 22:16:47 by mcouppe          ###   ########.fr       */
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

void	ft_fill_trim(t_trim *tr)
{
	tr->i = 0;
	tr->j = 0;
	tr->k = 0;
	while (tr->cmd && tr->cmd[tr->i])
	{
		if (tr->cmd[tr->i] == '"')
		{
			tr->k = 0;
			tr->i++;
			tr->c = '"';
			if (filling_tr(tr) == 1)
				w_condition_tr(tr);
		}
		else if (tr->cmd[tr->i] == '\'')
		{
			tr->i++;
			tr->c = '\'';
			if (filling_tr(tr) == 1)
				w_condition_tr(tr);
		}
		else
			tr->n_cmd[tr->j++] = tr->cmd[tr->i++];
	}
	tr->n_cmd[tr->j] = '\0';
}

void	ft_init_trim(t_trim *trim, int check, char *cmd)
{
	trim->i = 0;
	trim->j = 0;
	trim->cmd = cmd;
	trim->n_cmd = NULL;
	trim->check = check;
	trim->k = 0;
	trim->c = '"';
}

char	*strtrim_aug(char *cmd, int check)
{
	t_trim		trim;
	int			size;

	ft_init_trim(&trim, check, cmd);
	size = strtrim_size(&trim);
	if (ft_strnstr(trim.cmd, "export ", ft_strlen(trim.cmd)) != NULL)
		return (trim.cmd);
	if (ft_strnstr(trim.cmd, "echo ", ft_strlen(trim.cmd)) != NULL)
		return (trim.cmd);
	trim.n_cmd = malloc(sizeof(char) * size + 1);
	if (!trim.n_cmd)
		return (NULL);
	ft_fill_trim(&trim);
	if (trim.cmd)
		free(trim.cmd);
	return (trim.n_cmd);
}
