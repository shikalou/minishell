/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 17:05:43 by ldinaut           #+#    #+#             */
/*   Updated: 2021/11/30 19:00:12 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(int n)
{
	int		k;
	long	ln;

	ln = n;
	k = 1;
	if (ln < 0)
	{
		k += 1;
		ln *= -1;
	}
	while (ln >= 10)
	{
		ln = ln / 10;
		k++;
	}
	return (k);
}

char	*ft_itoa(int n)
{
	int				k;
	int				i;
	long			ln;
	char			*nb;

	k = ft_count(n);
	i = k;
	ln = n;
	nb = malloc(sizeof(char) * (k + 1));
	if (!nb)
		return (NULL);
	if (ln < 0)
	{
		nb[0] = '-';
		ln *= -1;
	}
	while (ln > 0 || (i == 1 && n == 0))
	{
		i--;
		nb[i] = (ln % 10) + 48;
		ln = ln / 10;
	}
	nb[k] = '\0';
	return (nb);
}

/*int	main()
{
	int n = 95978510;
	printf("%s\n", ft_itoa(n));
	return (0);
}*/
