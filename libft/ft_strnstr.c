/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 11:03:32 by ldinaut           #+#    #+#             */
/*   Updated: 2021/12/01 17:40:56 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	temp;

	i = 0;
	if (s2[0] == '\0')
		return ((char *)s1);
	while (s1[i])
	{
		temp = i;
		j = 0;
		while (s1[i] == s2[j] && i < n)
		{
			if (s2[j + 1] == '\0')
				return (&((char *)s1)[temp]);
			else
			{
				i++;
				j++;
			}
		}
		i = temp;
		i++;
	}
	return (NULL);
}
/*
#include <bsd/string.h>
int	main()
{
	char str[] = "bonjour comma comment commentaire ca va";
	char tofind[] = "come";

	printf("vrai %s\n", strnstr(str, tofind, 20));
	printf("moi %s\n", ft_strnstr(str, tofind, 20));
	return (0);
}*/
