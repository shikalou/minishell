/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:11:10 by ldinaut           #+#    #+#             */
/*   Updated: 2022/07/15 20:56:21 by mcouppe          ###   ########.fr       */
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

// too many line mais va falloir voir comment ca se goupille avec cmd_lst->command
int	ft_echo(t_big_struct *big_s, t_cmd_lst *cmd_lst)
{
	int	i;

	i = 1;
/*
	la meilleur tech serait de reprendre cmd_lst->command parce ke c la seule
	str ki conserve les espaces kon ait a dispo ici
	- mais du coup juste pour les putstr car les check de memcmp sont carres
	- et checker le nombre d'espaces entre echo et le reste (use strisalpha)
	- on update ce quon va print ds une str ki dup cmd_lst sans le echo koi
*/
	if (big_s->spaced_cmd[i] && ft_memcmp(big_s->spaced_cmd[i], "-n", 2) == 0)
	{
		if (ft_check_echo_n(big_s->spaced_cmd[i]))
		{
			while (ft_check_echo_n(big_s->spaced_cmd[i]))
				i++;
			ft_putstr_fd(big_s->spaced_cmd[i], cmd_lst->fd_out);
			if (big_s->spaced_cmd[i])
			{
				while (big_s->spaced_cmd[++i])
				{
					ft_putchar_fd(' ', cmd_lst->fd_out);
					ft_putstr_fd(big_s->spaced_cmd[i], cmd_lst->fd_out);
				}
			}
			return (0);
		}
	}
	else if (big_s->spaced_cmd[i])
	{
		ft_putstr_fd(big_s->spaced_cmd[i], cmd_lst->fd_out);
		while (big_s->spaced_cmd[++i])
		{
			ft_putchar_fd(' ', cmd_lst->fd_out);
			ft_putstr_fd(big_s->spaced_cmd[i], cmd_lst->fd_out);
		}
		ft_putchar_fd('\n', cmd_lst->fd_out);
	}
	else
		ft_putchar_fd('\n', cmd_lst->fd_out);
	return (0);
}
