/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cases.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <mcouppe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:09:07 by mcouppe           #+#    #+#             */
/*   Updated: 2022/07/16 20:47:16 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_first_case(t_big_struct *big_s, int i, char *cmd)
{
	int		j;

	j = i + 1;
	while (cmd[j] && (cmd[j] != ' ' && cmd[j] != '\0' && cmd[j] != '"'
			&& cmd[j] != '$' && cmd[j] != '\''))
		j++;
	if (cmd[i + 1] && cmd[i + 1] == '?' && ((j - i) == 2))
	{
		if (big_s->c_status != NULL)
		{
			free(big_s->c_status);
			big_s->c_status = NULL;
		}
		big_s->c_status = ft_itoa(big_s->status);
		return (big_s->c_status);
	}
	if ((j - i) == 1)
		return ("$");
	return (get_env_lst(cmd, (i + 1), j, big_s));
}

char	*expand_second_case(t_big_struct *big_s, int i, char *cmd)
{
	int		j;

	j = i;
	if (cmd[j] && (cmd[j] != ' ' && cmd[j] != '\0' && cmd[j] != '"'))
		j++;
	while (cmd[j] && (cmd[j] != ' ' && cmd[j] != '\0' && cmd[j] != '\''
			&& cmd[j] != '"' && cmd[j] != '$'))
		j++;
	if (cmd[i + 1] && cmd[i + 1] == '?' && ((j - i) == 2))
	{
		if (big_s->c_status != NULL)
		{
			free(big_s->c_status);
			big_s->c_status = NULL;
		}
		big_s->c_status = ft_itoa(big_s->status);
		return (big_s->c_status);
	}
	if ((j - i) == 1)
		return ("$");
	return (get_env_lst(cmd, i, j, big_s));
}
