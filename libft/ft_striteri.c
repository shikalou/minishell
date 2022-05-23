/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 18:49:19 by ldinaut           #+#    #+#             */
/*   Updated: 2021/11/27 12:56:46 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void	ft_topper(unsigned int i, char *s)
{
	(void)i;
	if (*s >= 'a' && *s <= 'z')
		*s = *s - 32;
}

void	ft_topper2(unsigned int i, char *s)
{
	(void)i;
	if (*s >= 'A' && *s <= 'Z')
		*s = *s + 32;
}*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/*
int	main()
{
	char s[] = "abc";
	ft_striteri(s, ft_topper);
	ft_putstr_fd(s,1);
	ft_striteri(s, ft_topper2);
	ft_putstr_fd(s,1);
	return (0);
}*/
