/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:53:21 by ldinaut           #+#    #+#             */
/*   Updated: 2021/11/30 16:02:31 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*dest;

	dest = malloc(size * count);
	if (!dest)
		return (NULL);
	ft_bzero(dest, size * count);
	return (dest);
}

/*int	main()
{
	int *str;
	int *str2;

	str = ft_calloc(3, 0);
	str2 = calloc(3, 0);
	printf("moi : %d,%d,%d\n", str[0], str[1], str[2]);
	printf("vrai : %d,%d,%d\n", str2[0], str2[1], str2[2]);
	return (0);
}*/
