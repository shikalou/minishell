/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:39:08 by ldinaut           #+#    #+#             */
/*   Updated: 2022/07/14 15:54:48 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned long long int	ft_atol(const char *str)
{
	int				i;
	int				sign;
	unsigned long long int	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while ((str[i] >= 8 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && nb < LONG_MAX)
	{
		nb = nb * 10 + (str[i] - 48);
		printf("dans la boucle %llu\n", nb);
		i++;
	}
	printf("hoho nb = %llu\n", nb * sign);
	return (nb * sign);
}

int	ft_check_arg(char *s)
{
	int			i;
	unsigned long long int	nb;

	i = 0;
	if (s[i] == '-')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	if (s[0] == '-')
		nb = ft_atol(s + 1);
	else
		nb = ft_atol(s);
	printf("ihih nb = %llu\n", nb);
	if (nb > LONG_MAX)
		return (0);
	return (1);
}

void	ft_exit(t_big_struct *b)
{
	int	i;

	i = 1;
	if (b->spaced_cmd[i])
	{
		if (ft_check_arg(b->spaced_cmd[i]))
		{
			if (b->spaced_cmd[i + 1])
			{
				printf("%s: too many arguments\n", b->spaced_cmd[0]);
				b->status = 1;
				return ;
			}
			else
				b->status = ft_atol(b->spaced_cmd[i]);
		}
		else
		{
			printf("%s: %s: numeric argument required\n", b->spaced_cmd[0], b->spaced_cmd[1]);
			b->status = 2;
			return ;
		}
	}
	ft_free_tab(b->spaced_cmd);
	if (b->spaced_cmd[1][0] != '-')
		i = (b->status % 256);
	else
	{
		i = (256 - b->status % 256);
	}
	ft_free_child(b, 1);
	exit(i);
}
