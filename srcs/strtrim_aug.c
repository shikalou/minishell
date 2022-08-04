/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtrim_aug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:53:29 by mcouppe           #+#    #+#             */
/*   Updated: 2022/08/04 22:05:16 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_without_tr(t_trim *tr)
{
	while (tr->cmd[tr->i] != tr->c)
	{
		tr->n_cmd[++tr->j] = tr->cmd[tr->i];
		tr->i++;
	}
}

int	strtrim_size(t_trim *tr)
{
	if (!tr->cmd)
		return (tr->i);
	while (tr->cmd && tr->cmd[++tr->i] != '\0')
	{
		if (tr->cmd[tr->i] == '"')
		{
			tr->i++;
			tr->j += 2;
			tr->c = '"';
			while (tr->cmd[tr->i] != tr->c)
				tr->i++;
		}
		else if (tr->cmd[tr->i] == '\'')
		{
			tr->i++;
			tr->j += 2;
			tr->c = '\'';
			while (tr->cmd[tr->i] != tr->c)
				tr->i++;
		}
	}
	return (tr->i - tr->j);
}

void	ft_fill_trim(t_trim *tr)
{
	tr->i = -1;
	tr->j = -1;
	tr->k = 0;
	while (tr->cmd && tr->cmd[++tr->i])
	{
		if (tr->cmd[tr->i] == '"')
		{
			tr->i++;
			tr->c = '"';
			fill_without_tr(tr);
		}
		else if (tr->cmd[tr->i] == '\'')
		{
			tr->i++;
			tr->c = '\'';
			fill_without_tr(tr);
		}
		else
			tr->n_cmd[++tr->j] = tr->cmd[tr->i];
	}
	tr->n_cmd[++tr->j] = '\0';
}

void	ft_init_trim(t_trim *trim, int check, char *cmd)
{
	trim->i = -1;
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
	trim.n_cmd = malloc(sizeof(char) * size + 1);
	if (!trim.n_cmd)
		return (NULL);
	ft_fill_trim(&trim);
	if (trim.cmd)
		free(trim.cmd);
	return (trim.n_cmd);
}
