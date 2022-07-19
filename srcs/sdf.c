/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_du_futur.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:18:19 by ldinaut           #+#    #+#             */
/*   Updated: 2022/07/19 14:53:06 by ldinaut          ###   ########.fr       */
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

// fo ranger ft test lol
static char	**ft_fill_strs(char **strs, const char *s1, char c, int check)
{
	int		i;
	int		j;
	int		l;

	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		l = 0;
		check = 0;
		while (s1[i] && s1[i] != c && s1[i + 1])
		{
			if (s1[i] == '"' || s1[i] == '\'')
			{
				check = i + (ft_split_quotes(s1, i) + 1);
				while (s1[i] && (i <= check))
					strs[j][l++] = s1[i++];
			}
			else
				strs[j][l++] = s1[i++];
		}
		if (s1[i] && (s1[i] != c) && !(s1[i + 1]))
			strs[j][l++] = s1[i];
		strs[j][l] = '\0';
		j++;
		if (s1[i])
			i++;
	}
	strs[j] = NULL;
	return (strs);
}

char	**ft_sdf(char const *s1, char c)
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
		i += l;
		if (!strs[j])
			ft_free(strs, j);
	}
	ft_fill_strs(strs, s1, c, 0);
	return (strs);
}

/*int main()
{
	char	**split;
	char *hihi = "lol | lil | \"merde test|test\"ui oui | nn non";
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
