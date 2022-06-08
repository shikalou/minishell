/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extended_parse_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:49:15 by mcouppe           #+#    #+#             */
/*   Updated: 2022/06/08 15:06:06 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_memchr_aug(char *s, int i, char c)
{
	i++;
	while (s[i] && s[i] != '\'')
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_len_dollar(char *cmd, int i)
{
	int	j;

	j = 0;
	while (cmd[i])
	{
		if (cmd[i] == '$')
		{
			while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\''
				&& cmd[i] != '"')
			{
				i++;
				j++;
			}
			return (j);
		}
		i++;
	}
	j = 1;
	return (j);
}
