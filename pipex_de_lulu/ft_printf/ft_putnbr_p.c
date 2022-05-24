/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:52:12 by ldinaut           #+#    #+#             */
/*   Updated: 2021/12/08 16:59:33 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_p(unsigned long long n, int c)
{
	char	*base;
	int		i;

	if (c != 0)
		write(1, "0x", 2);
	base = "0123456789abcdef";
	if (n < 16)
		ft_putchar_fd(base[n % 16], 1);
	else
	{
		ft_putnbr_p(n / 16, 0);
		ft_putchar_fd(base[n % 16], 1);
	}
	i = ft_countnb_hex(n);
	return (i + 2);
}
