/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 17:34:34 by ldinaut           #+#    #+#             */
/*   Updated: 2022/03/04 18:13:39 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stddef.h>
# include <stdarg.h>

int		ft_printf(const char *s, ...);
int		ft_putunbr_fd(unsigned int n, int fd);
int		ft_putnbrhexa_fd(unsigned int n, char c);
int		ft_putnbr_p(unsigned long long n, int c);
int		ft_putd(int n, int fd);
int		ft_puts(char *s, int fd);
int		ft_putc(char c, int fd);
int		ft_countnb(int n);
int		ft_countnb_hex(unsigned long long n);
int		ft_countunb(unsigned int n);

void	ft_dispense(const char *s, size_t *count, va_list args, int i);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);

#endif
