/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:18:19 by ldinaut           #+#    #+#             */
/*   Updated: 2022/06/01 16:41:22 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_split_quotes(const char *s1, int i)
{
	int	k;
	char	d;

	k = 0;
	d = s1[i];
	while(s1[++i] != d)
		k++;
	return (k);
}

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

static char	**ft_test(char **strs, const char *s1, char c, int check)
{
	int	i;
	int	j;
	int	l;

	i = -1;
	j = 0;
	printf("debut test\n");
	while (s1 && s1[++i])
	{
		l = 0;
		check = 0;
		while (s1[i] && s1[i] != c)
		{
			if (s1[i] == '"' || s1[i] == '\'')
			{
				check = i +  ft_split_quotes(s1, i);
				while (s1[i] && (i < check))
					strs[j][l++] = s1[i++];
			}
			else
				strs[j][l++] = s1[i++];
		}
		strs[j++][l] = '\0';
	}
	printf("fin test\n");
	strs[j] = NULL;
	return (strs);
}

static int	ft_count_char(char const *s1, int i, char c)
{
	int	k;

	k = 0;
	printf("debut count char\n");
	while (s1[i] && s1[i] != c)
	{
		if (s1[i] == '"' || s1[i] == '\'')
		{
			k += ft_split_quotes(s1, i);
			i += ft_split_quotes(s1, i);
		}
		k++;
		i++;
	}
	printf("fin count char \n");
	return (k);
}

static int	ft_count_strs(char const *s1, char c)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	printf("debut count strs\n");
	while (s1[i])
	{
		while (s1[i] && s1[i] == c)
			i++;
		if (s1[i] && s1[i] != c)
		{
			k++;
			while (s1[i] && s1[i] != c)
			{
				if (s1[i] && (s1[i] == '"' || s1[i] == '\''))
				{
					i += ft_split_quotes(s1, i);
				}
				i++;
			}
		}
	}
	printf("fin count strs\n");
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
	ft_test(strs, s1, c, 0);
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