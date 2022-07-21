/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:18:19 by ldinaut           #+#    #+#             */
/*   Updated: 2022/07/21 16:42:04 by mcouppe          ###   ########.fr       */
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

static char	**ft_fill_strs(t_sdf *sdf, int check)
{
	while (sdf->s && sdf->s[sdf->i])
	{
		sdf->l = 0;
		check = 0;
		while (sdf->s[sdf->i] && sdf->s[sdf->i] == sdf->c)
				sdf->i++;
		while (sdf->s[sdf->i] && sdf->s[sdf->i] != sdf->c && sdf->s[sdf->i + 1])
		{
			if (sdf->s[sdf->i] == '"' || sdf->s[sdf->i] == '\'')
			{
				check = sdf->i + (ft_split_quotes(sdf->s, sdf->i) + 1);
				while (sdf->s[sdf->i] && (sdf->i <= check))
					sdf->strs[sdf->j][sdf->l++] = sdf->s[sdf->i++];
			}
			else
				sdf->strs[sdf->j][sdf->l++] = sdf->s[sdf->i++];
		}
		if (sdf->s[sdf->i] && (sdf->s[sdf->i] != sdf->c) && !(sdf->s[sdf->i + 1]))
			sdf->strs[sdf->j][sdf->l++] = sdf->s[sdf->i++];
		sdf->strs[sdf->j][sdf->l] = '\0';
		sdf->j++;
		if (sdf->s[sdf->i] && sdf->s[sdf->i] == sdf->c)
		{
			while (sdf->s[sdf->i] && sdf->s[sdf->i] == sdf->c)
				sdf->i++;
		}
	}
	sdf->strs[sdf->j] = NULL;
	return (sdf->strs);
}

char	**ft_sdf(char const *s1, char c)
{
	t_sdf		sdf;
	int			i;
	int			j;
	int			l;

	i = 0;
	j = -1;
	ft_init_sdf(&sdf, s1, c);
	sdf.strs = malloc(sizeof(char *) * (sdf.k + 1));
	if (!sdf.strs)
		return (NULL);
	while (sdf.s && ++j < sdf.k)
	{
		while (sdf.s[i] && sdf.s[i] == c)
			i++;
		if (s1[i] != c)
			l = ft_count_char(s1, i, c);
		sdf.strs[j] = malloc(sizeof(char) * (l + 1));
		i += l;
		if (!sdf.strs[j])
			ft_free(sdf.strs, j);
	}
	ft_fill_strs(&sdf, 0);
	return (sdf.strs);
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
