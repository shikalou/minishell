/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 18:15:17 by ldinaut           #+#    #+#             */
/*   Updated: 2021/12/01 15:15:31 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	char			d;

	d = c;
	i = 0;
	while (s[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (s[i] == d)
			return (&((char *)s)[i]);
		i--;
	}
	return (0);
}
/*
int     main()
{
        char str[]= "blablalaevnvngjjfj";
        int c = 106;
        printf("moi : %s\n", ft_strrchr(str, c));
        printf("vrai : %s\n", strrchr(str, c));
        return (0);
}*/
