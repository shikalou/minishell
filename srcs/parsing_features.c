/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_features.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <mcouppe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 12:17:33 by mcouppe           #+#    #+#             */
/*   Updated: 2022/08/05 15:20:07 by mcouppe          ###   ########.fr       */
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

int	check_rafter(char *cmd, char o_rafter, char c_rafter, int i)
{
	while (cmd && cmd[++i])
	{
		if (cmd[i] == o_rafter)
		{
			i++;
			while (cmd[i] && cmd[i] == ' ')
				i++;
			if (cmd[i] == c_rafter)
				return (1);
		}
		else if (cmd[i] == c_rafter)
		{
			i++;
			if (cmd[i] == ' ')
			{
				while (cmd[i] == ' ')
				{
					i++;
					if (cmd[i] == o_rafter)
						return (1);
				}
			}
		}
	}
	return (0);
}

int	error_parse(t_big *b)
{
	write(2, "Syntax error\n", 13);
	b->status = 2;
	ft_free_tab(b->input);
	b->input = NULL;
	return (1);
}

int	is_only_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}
