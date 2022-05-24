/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:39:47 by ldinaut           #+#    #+#             */
/*   Updated: 2021/12/08 18:52:19 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunbr_fd(unsigned int n, int fd)
{
	unsigned int	nb;
	int				i;

	nb = n;
	i = ft_countunb(nb);
	if (nb < 10)
	{
		nb = nb + '0';
		ft_putchar_fd(nb, fd);
	}
	else
	{
		ft_putunbr_fd(nb / 10, fd);
		ft_putunbr_fd(nb % 10, fd);
	}
	return (i);
}

/*int main()
{
	printf("%d",size_ofnb(99123));
	return (0);
}*/