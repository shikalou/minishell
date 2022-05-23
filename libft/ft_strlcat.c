/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:52:58 by ldinaut           #+#    #+#             */
/*   Updated: 2021/11/25 19:42:49 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = ft_strlen(dst);
	if (size <= k)
		return (ft_strlen(src) + size);
	while (dst[i])
		i++;
	while (src[j] && i < (size - 1))
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (k + ft_strlen(src));
}

/*#include <bsd/string.h>
int	main()
{
	char dst[] = "toto";
	char dst2[] = "toto";
	char src[] = "blabla";
	char src2[] = "blabla";
	size_t size = 9;
	
	printf("vrai : %zu\n", strlcat(dst, src, size));
	printf("dest apres : %s\n", dst);
	printf("moi : %zu\n", ft_strlcat(dst2, src2, size));
	printf("dest2 apres : %s\n", dst2);
	return (0);
}*/
