/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 13:27:53 by ldinaut           #+#    #+#             */
/*   Updated: 2021/11/30 14:56:53 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (dest);
	if (!(dest || src))
		return (0);
	if ((src + n) < dest || src > dest)
	{
		while (i < n)
		{
			((char *)dest)[i] = ((const char *)src)[i];
			i++;
		}
	}
	else
	{
		i = n;
		while (i > 0)
		{
			i--;
			((char *)dest)[i] = ((const char *)src)[i];
		}
	}
	return (dest);
}

/*int	main()
{
	char  src[] = NULL;
	char src2[] = NULL;
	char dest[15] = "42";
	char dest2[15] = "42";
	printf("moi grace a julien %s\n", (char *)ft_memmove(dest, src, NULL));
	printf("vrai %s\n", memmove(dest2, src2, NULL));
	printf("tkt ca marche : %s\n", src);
	printf("tkt ca marche : %s\n", src2);
	return (0);
}*/
