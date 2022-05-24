/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 18:44:42 by ldinaut           #+#    #+#             */
/*   Updated: 2022/03/02 17:39:30 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_free(char **strs, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

static char	**ft_fill_strs(char **strs, const char *s1, char c)
{
	int	i;
	int	j;
	int	l;

	i = 0;
	j = -1;
	while (s1 && s1[i])
	{
		l = 0;
		while (s1[i] && s1[i] == c)
			i++;
		if (s1[i])
		{
			j++;
			while (s1[i] && s1[i] != c)
				strs[j][l++] = s1[i++];
			strs[j][l] = '\0';
		}
		while (s1[i] && s1[i] == c)
			i++;
	}
	strs[j + 1] = NULL;
	return (strs);
}

static int	ft_count_char(char const *s1, int i, char c)
{
	int	k;

	k = 0;
	while (s1[i] && s1[i] != c)
	{
		k++;
		i++;
	}
	return (k);
}

static int	ft_count_strs(char const *s1, char c)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	if (!s1)
		return (0);
	while (s1[i])
	{
		while (s1[i] && s1[i] == c)
			i++;
		if (s1[i] && s1[i] != c)
		{
			k++;
			while (s1[i] && s1[i] != c)
				i++;
		}
	}
	return (k);
}

char	**ft_split(char const *s1, char c)
{
	int			i;
	int			k;
	int			j;
	int			l;
	char		**strs;

	i = 0;
	j = -1;
	k = ft_count_strs(s1, c);
	strs = malloc(sizeof(char *) * (k + 1));
	if (!strs)
		return (NULL);
	while (s1 && ++j < k)
	{
		while (s1[i] && s1[i] == c)
			i++;
		if (s1[i] != c)
			l = ft_count_char(s1, i, c);
		strs[j] = malloc(sizeof(char) * (l + 1));
		i += l + 1;
		if (!strs[j])
			ft_free(strs, j);
	}
	ft_fill_strs(strs, s1, c);
	return (strs);
}
