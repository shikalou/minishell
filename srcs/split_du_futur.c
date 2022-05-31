/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_du_futur.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:18:19 by ldinaut           #+#    #+#             */
/*   Updated: 2022/05/31 14:37:26 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	**ft_test(char **strs, const char *s1, char c)
{
	int	i;
	int	j;
	int	l;
	int	check;

	i = 0;
	j = 0;
	check = 0;
	while (s1 && s1[i])
	{
		l = 0;
		check = 0;
		if (s1[i])
		{
			while (s1[i] && s1[i] != c)
			{
				if (s1[i] == '"' && check == 0)
				{
					check++;
					strs[j][l++] = s1[i++];
					while (s1[i] && s1[i] != '"')
						strs[j][l++] = s1[i++];
				}
				else
					strs[j][l++] = s1[i++];
			}
			strs[j][l] = '\0';
			while (s1[i] && s1[i] == c)
				i++;
		}
		j++;
	}
	strs[j] = NULL;
	return (strs);
}

static int	ft_count_char(char const *s1, int i, char c)
{
	int	k;

	k = 0;
	while (s1[i] && s1[i] != c)
	{
		if (s1[i] == '"')
		{
			i++;
			while (s1[i] != '"')
			{
				k++;
				i++;
			}
			k++;
		}
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
			{
				if (s1[i] && s1[i] == '"')
				{
					while (s1[++i] != '"')
						;
				}
				i++;
			}
		}
	}
	return (k);
}

char	**ft_split_du_futur(char const *s1, char c)
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
	ft_test(strs, s1, c);
	return (strs);
}

/*int main()
{
	char	**split;
	char *hihi = "lol | lil | \"merde test|test\" mdrr | ahahaha | \"connard | salopiaud \" oui oui | nn non";
	printf("%s\n", hihi);
	split = ft_split_du_futur(hihi, '|');
	int i;
	i = 0;
	while (split[i])
	{
		printf("%s\n", split[i]);
		i++;
	}
	return 0;
}*/
