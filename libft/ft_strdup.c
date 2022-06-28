/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:15:37 by ldinaut           #+#    #+#             */
/*   Updated: 2022/06/28 11:00:43 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int			i;
	char		*dest;

	i = 0;
	dest = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!dest)
		return (NULL);
	while (s1 && s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/*int	main()
{
	char str[] = "qwertyvbnm,.klrhlerht ortrght rhkdjghdlh";
	printf("vrai : %s\n", strdup(str));
	printf("moi : %s\n", ft_strdup(str));
	return (0);
}*/
