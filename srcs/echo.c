/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:11:10 by ldinaut           #+#    #+#             */
/*   Updated: 2022/07/19 14:10:32 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_echo_n(char *s)
{
	int	i;

	i = 1;
	if (!s)
		return (0);
	while (s && s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	echo_putstr(t_big *big_s, t_cmd_lst *cmd_lst, int i)
{
	ft_putstr_fd(big_s->spaced_cmd[i], cmd_lst->fd_out);
	while (big_s->spaced_cmd[++i])
	{
		ft_putchar_fd(' ', cmd_lst->fd_out);
		ft_putstr_fd(big_s->spaced_cmd[i], cmd_lst->fd_out);
	}
}

int	ft_echo(t_big *big_s, t_cmd_lst *cmd_lst)
{
	int	i;

	i = 1;
	if (big_s->spaced_cmd[i] && ft_memcmp(big_s->spaced_cmd[i], "-n", 2) == 0)
	{
		if (ft_check_echo_n(big_s->spaced_cmd[i]))
		{
			while (ft_check_echo_n(big_s->spaced_cmd[i]))
				i++;
			echo_putstr(big_s, cmd_lst, i);
			big_s->status = 0;
			return (1);
		}
	}
	if (big_s->spaced_cmd[i])
	{
		echo_putstr(big_s, cmd_lst, i);
		ft_putchar_fd('\n', cmd_lst->fd_out);
	}
	else
		ft_putchar_fd('\n', cmd_lst->fd_out);
	big_s->status = 0;
	return (1);
}
