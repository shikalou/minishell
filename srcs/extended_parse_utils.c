/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extended_parse_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:49:15 by mcouppe           #+#    #+#             */
/*   Updated: 2022/06/14 12:06:00 by ldinaut          ###   ########.fr       */
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
			if (cmd[i] && cmd[i] != ' ' && cmd[i] != '\''
				&& cmd[i] != '"')
			{
				i++;
				j++;
			}
			while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\''
				&& cmd[i] != '"' && cmd[i] != '$')
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
