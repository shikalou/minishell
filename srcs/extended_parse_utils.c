/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extended_parse_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:49:15 by mcouppe           #+#    #+#             */
/*   Updated: 2022/08/04 22:29:02 by ldinaut          ###   ########.fr       */
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
				&& cmd[i] != '"' && cmd[i] != '$' && cmd[i] != '=')
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

char	*expand_status(char *b_status, char *cmd, int index, t_big *b)
{
	int		i;
	int		j;
	char	*end;

	i = index + 2;
	j = 0;
	if (cmd[++index + 1] && cmd[index + 1] != '\0' && cmd[index + 1] != ' '
		&& cmd[i] != '"' && cmd[i] != '\'')
	{
		index++;
		while (cmd[i] && cmd[i] != ' ' && cmd[i] != '$' && cmd[i] != '"'
			&& cmd[i] != '\'')
			i++;
		end = malloc(sizeof(char) * (i - index) + 1);
		if (!end)
			return (NULL);
		while (index < i)
			end[j++] = cmd[index++];
		end[j] = '\0';
		b->check_expand_status = 1;
		return (free(end), ft_strjoin(b_status, end));
	}
	b->check_expand_status = 0;
	return (b_status);
}

void	strtrim_new(char **tab)
{
	int	i;

	i = 0;
	if (ft_memcmp(tab[0], "export", 7) == 0)
		return ;
	while (tab[i])
	{
		tab[i] = strtrim_aug(tab[i], 0);
		i++;
	}
}
