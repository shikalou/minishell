/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 16:18:47 by ldinaut           #+#    #+#             */
/*   Updated: 2021/12/09 15:22:43 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_dispense(const char *s, size_t *count, va_list args, int i)
{
	while (s[++i])
	{
		if (s[i] == '%')
		{
			i++;
			if (s[i] == 'd' || s[i] == 'i')
				*count += ft_putd(va_arg(args, int), 1);
			else if (s[i] == 'c')
				*count += ft_putc(va_arg(args, int), 1);
			else if (s[i] == 's')
				*count += ft_puts(va_arg(args, char *), 1);
			else if (s[i] == 'x' || s[i] == 'X')
				*count += ft_putnbrhexa_fd(va_arg(args, unsigned int), s[i]);
			else if (s[i] == 'u')
				*count += ft_putunbr_fd(va_arg(args, unsigned int), 1);
			else if (s[i] == '%')
				*count += ft_putc('%', 1);
			else if (s[i] == 'p')
				*count += ft_putnbr_p(va_arg(args, unsigned long long), 1);
		}
		else
			*count += write(1, &s[i], 1);
	}
}

int	ft_printf(const char *s, ...)
{
	size_t	count;
	va_list	args;
	int		i;

	i = -1;
	va_start(args, s);
	count = 0;
	ft_dispense(s, &count, args, i);
	va_end(args);
	return (count);
}
