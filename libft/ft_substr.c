/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:45:07 by ldinaut           #+#    #+#             */
/*   Updated: 2021/11/27 14:24:08 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*dest;
	size_t			i;
	size_t			k;

	i = 0;
	if (start > ft_strlen(s))
		k = 0;
	else
	{
		k = (ft_strlen(s) - start);
		if (k > len)
			k = len;
	}
	dest = malloc(sizeof(char) * (k + 1));
	if (!dest)
		return (NULL);
	while (i < k)
	{
		dest[i] = s[start];
		i++;
		start++;
	}
	dest[i] = '\0';
	return (dest);
}
/*
int	main()
{
	char str[] = "0123456789";
	unsigned int start = 11;
	size_t len = 6;
	char *str2;
	str2 = ft_substr(str, start, len);
	//printf("address : %p\n", str2);
	printf("%s\n", str2);
	free(str2);
	return (0);
}*/
