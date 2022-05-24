/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_substitute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:58:32 by ldinaut           #+#    #+#             */
/*   Updated: 2022/03/21 21:46:00 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strchr(const char *s, int c)
{
	int			i;
	char		d;

	i = 0;
	d = c;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == d)
			return (&((char *)s)[i]);
		i++;
	}
	if (c == 0)
		return (&((char *)s)[i]);
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	int			i;
	char		*dest;

	i = 0;
	dest = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!dest)
		return (NULL);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int			i;
	int			j;
	int			k;
	char		*dest;

	i = -1;
	j = 0;
	if (!s2 || !s1)
		return (NULL);
	k = (ft_strlen(s1) + ft_strlen(s2));
	dest = malloc(sizeof(char) * (k + 1));
	if (!dest)
		return (NULL);
	while (s1 && s1[++i])
		dest[i] = s1[i];
	while (s2 && s2[j])
	{
		dest[i] = s2[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}
