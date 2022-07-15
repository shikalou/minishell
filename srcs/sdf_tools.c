/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdf_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <mcouppe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 21:43:58 by mcouppe           #+#    #+#             */
/*   Updated: 2022/07/15 21:52:08 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_split_quotes(const char *s1, int i)
{
	int		k;
	char	d;

	k = 0;
	d = s1[i];
	while (s1[i] && s1[++i] != d)
		k++;
	return (k);
}

int	ft_count_char(char const *s1, int i, char c)
{
	int		k;

	k = 0;
	while (s1[i] && s1[i] != c)
	{
		if (s1[i] == '"' || s1[i] == '\'')
		{
			k += (ft_split_quotes(s1, i) + 1);
			i += (ft_split_quotes(s1, i) + 1);
		}
		k++;
		i++;
	}
	return (k);
}

int	ft_count_strs(char const *s, char c)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (s && s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			k++;
			while (s[i] && s[i] != c)
			{
				if (s[i] && (s[i] == '"' || s[i] == '\''))
					i += (ft_split_quotes(s, i) + 1);
				i++;
			}
		}
	}
	return (k);
}
