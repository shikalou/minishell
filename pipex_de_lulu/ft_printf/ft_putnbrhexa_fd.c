/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrhexa_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:36:12 by ldinaut           #+#    #+#             */
/*   Updated: 2021/12/08 17:02:22 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbrhexa_fd(unsigned int n, char c)
{
	long unsigned int	nb;
	char				*base;
	int					i;

	nb = n;
	if (c == 'X')
		base = "0123456789ABCDEF";
	if (c == 'x')
		base = "0123456789abcdef";
	if (nb < 16)
		ft_putchar_fd(base[nb % 16], 1);
	else
	{
		ft_putnbrhexa_fd(nb / 16, c);
		ft_putchar_fd(base[nb % 16], 1);
	}
	i = ft_countnb_hex(nb);
	return (i);
}
