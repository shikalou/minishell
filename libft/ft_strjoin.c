/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:07:45 by ldinaut           #+#    #+#             */
/*   Updated: 2022/07/21 20:03:51 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int			i;
	int			j;
	int			k;
	char		*dest;

	i = 0;
	j = 0;
	if (s2 == NULL || !s2 || s2[j] == '\0')
		return (ft_strdup(s1));
	k = (ft_strlen(s1) + ft_strlen(s2));
	dest = malloc(sizeof(char) * (k + 1));
	if (!dest)
		return (NULL);
	while (s1 && s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
		dest[i++] = s2[j++];
	dest[i] = '\0';
	return (dest);
}

/*int	main()
{
	char s1[] = "salut c cool";
	char s2[] = "lololololol";
	printf("%s\n", ft_strjoin(s1, s2));
	return (0);
}*/
