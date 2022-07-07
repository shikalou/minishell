/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 18:43:25 by ldinaut           #+#    #+#             */
/*   Updated: 2022/07/07 20:26:35 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	if (!s1 || !s1[i])
		return (1);
	while (s1[i] && i < (n - 1))
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

/*int	main()
{
	char s1[] = "bmabmabla";
	char s2[] = "blablabla";
	printf("moi %d\n", ft_strncmp(s1, s2, 0));
	printf("vrai %d\n", strncmp(s1, s2, 0));
	return (0);
}*/
