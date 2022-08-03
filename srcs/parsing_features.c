/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_features.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 12:17:33 by mcouppe           #+#    #+#             */
/*   Updated: 2022/08/03 14:23:22 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_checkquotes(char *cmd)
{
	int	i;

	i = -1;
	while (cmd && cmd[++i])
	{
		if (cmd[i] && cmd[i] == '\'')
		{
			while (cmd[i] && cmd[++i] && cmd[i] != '\'')
				;
			if (!cmd[i])
				return (1);
		}
		if (cmd[i] && cmd[i] == '\"')
		{
			while (cmd[i] && cmd[++i] && cmd[i] != '\"')
				;
			if (!cmd[i])
				return (1);
		}
	}
	return (0);
}

int	check_after_pipe(char *cmd, char c, int j, int i)
{
	while (cmd && cmd[++i] && cmd[i] != '\0')
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
			i += (ft_split_quotes(cmd, i) + 1);
		if (cmd[i] && cmd[i] == c)
		{
			i++;
			j = 0;
			while (cmd && cmd[i++] && cmd[i] != '\0')
			{
				if (cmd[i] == '\'' || cmd[i] == '"')
					j += ft_split_quotes(cmd, i) + 1;
				else if (cmd[i] != '\0' && ft_isalnum(cmd[i]) == 1)
					j++;
			}
			if (j == 0)
				return (1);
			else
				i = (i - j);
			if (i <= 0)
				return (0);
		}
	}
	return (0);
}

int	error_parse(t_big *b)
{
	write(2, "Error syntax\n", 13);
	b->status = 2;
	ft_free_tab(b->input);
	b->input = NULL;
	return (1);
}
