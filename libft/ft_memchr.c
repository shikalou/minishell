/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:59:04 by ldinaut           #+#    #+#             */
/*   Updated: 2021/12/01 15:14:05 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned char		d;

	d = c;
	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == d)
			return (&((unsigned char *)s)[i]);
		i++;
	}
	return (0);
}
/*
int	main()
{
	char str[]= {0, 1, 2 ,3 ,4 ,5};
	int c = 2 + 256;
	printf("%d\n", c);
	printf("moi : %s\n", ft_memchr(str, c, 3));
	printf("vrai : %s\n", memchr(str, c, 3));
	return (0);
}*/
