/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:09:41 by ldinaut           #+#    #+#             */
/*   Updated: 2021/11/29 16:32:30 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
/*
#include <bsd/string.h>
int main()
{
	char *src = "ui";
	char dest[10];
	char *src2 = "ui";
	char dest2[10];
	printf("vrai %zu\n", strlcpy(dest2, src2, 6));
	printf("moi %zu\n", ft_strlcpy(dest, src, 6));
	printf("dest apres %s\n", dest);
	printf("dest2 apres %s\n", dest2);
	return (0);
}*/
