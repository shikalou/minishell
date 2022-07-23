/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtrim_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 21:43:57 by mcouppe           #+#    #+#             */
/*   Updated: 2022/07/23 22:12:30 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	filling_tr(t_trim *tr)
{
	if (tr->cmd[tr->i] == tr->c && tr->check == 0)
	{
		tr->n_cmd[tr->j++] = tr->cmd[tr->i];
		tr->n_cmd[tr->j++] = tr->cmd[tr->i++];
		tr->check++;
	}
	else if (tr->cmd[tr->i] == tr->c && tr->check != 0)
		tr->i++;
	else if (tr->cmd[tr->i] == ' ')
	{
		while (tr->cmd[tr->i] && tr->cmd[tr->i] == ' '
			&& tr->cmd[tr->i++] != tr->c)
			tr->k++;
		if (tr->cmd[tr->i] == tr->c)
		{
			tr->n_cmd[tr->j++] = tr->cmd[tr->i];
			tr->n_cmd[tr->j++] = tr->cmd[tr->i++];
		}
		else
			tr->i -= tr->k;
		w_condition_tr(tr);
	}
	else
		return (1);
	return (0);
}

void	w_condition_tr(t_trim *tr)
{
	while (tr->cmd[tr->i] && tr->cmd[tr->i] != tr->c)
		tr->n_cmd[tr->j++] = tr->cmd[tr->i++];
}
