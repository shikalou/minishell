/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:39:08 by ldinaut           #+#    #+#             */
/*   Updated: 2022/06/30 16:20:29 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_arg(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
	}
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
				b->status = ft_atoi(b->spaced_cmd[i]);
		}
		else
		{
			printf("%s: %s: numeric argument required\n", b->spaced_cmd[0], b->spaced_cmd[1]);
			b->status = 2;
			return ;
		}
	}
	ft_free_tab(b->spaced_cmd);
	i = (b->status % 256);
	ft_free_child(b);
	exit(i);
}

