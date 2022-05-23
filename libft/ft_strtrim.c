/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:33:00 by ldinaut           #+#    #+#             */
/*   Updated: 2021/11/30 17:46:39 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*fill_tab(char *dest, const char *s1, int i, int j)
{
	int	l;

	l = 0;
	while (i <= j)
	{
		dest[l] = s1[i];
		i++;
		l++;
	}
	dest[l] = '\0';
	return (dest);
}

static int	ft_is_char(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		else
			i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int			i;
	int			j;
	int			k;
	char		*dest;

	i = 0;
	if (!s1)
		return (NULL);
	j = (ft_strlen(s1) - 1);
	while (ft_is_char(s1[i], set))
		i++;
	while (ft_is_char(s1[j], set))
		j--;
	if (j >= i)
		k = ((j - i) + 1);
	else
		k = 0;
	dest = malloc(sizeof(char) * (k + 1));
	if (!dest)
		return (NULL);
	dest = fill_tab(dest, s1, i, j);
	return (dest);
}
/*
int	main()
{
	char s1[] = " ";
	char set[] = " ";
	printf("%s\n", ft_strtrim(s1, set));
	return (0);
}*/
