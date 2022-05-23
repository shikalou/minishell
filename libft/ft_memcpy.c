/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 12:58:17 by ldinaut           #+#    #+#             */
/*   Updated: 2021/11/30 14:55:26 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!(s1 || s2))
		return (0);
	while (i < n)
	{
		((char *)s1)[i] = ((char *)s2)[i];
		i++;
	}
	return (s1);
}
/*
int	main()
{
	char *src;
	//char dest[6];
	//ft_memcpy(NULL, NULL, 5);
	src = memcpy(NULL, NULL, 5);
	printf("%s\n", src);
	return (0);
}*/
