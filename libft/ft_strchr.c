/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:01:27 by ldinaut           #+#    #+#             */
/*   Updated: 2021/12/01 15:17:10 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int			i;
	char		d;

	i = 0;
	d = c;
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
/*
int	main()
{
	char str[]= "tripouille";
	int c = 't' + 256;
	printf("ici %d et %c\n", c, c);
	printf("moi : %s\n", ft_strchr(str, c));
	printf("vrai : %s\n", strchr(str, c));
	return (0);
}*/
