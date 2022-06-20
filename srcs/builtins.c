/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:12:57 by ldinaut           #+#    #+#             */
/*   Updated: 2022/06/20 19:21:21 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_big_struct *big_struct, t_cmd_lst *cmd_lst)
{
	ft_putstr_fd(big_struct->absolut_path, cmd_lst->fd_out);
}

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

void	ft_echo(t_big_struct *big_struct, t_cmd_lst *cmd_lst)
{
	int	i;

	i = 1;
	if (big_struct->spaced_cmd[i] && ft_memcmp(big_struct->spaced_cmd[i], "-n", 2) == 0)
	{
		if (ft_check_echo_n(big_struct->spaced_cmd[i]))
		{
			while (ft_check_echo_n(big_struct->spaced_cmd[i]))
				i++;
			ft_putstr_fd(big_struct->spaced_cmd[i], cmd_lst->fd_out);
			if (big_struct->spaced_cmd[i])
			{
				while (big_struct->spaced_cmd[++i])
				{
					ft_putchar_fd(' ', cmd_lst->fd_out);
					ft_putstr_fd(big_struct->spaced_cmd[i], cmd_lst->fd_out);
				}
			}
			return ;
		}
	}
	else if (big_struct->spaced_cmd[i])
	{
		ft_putstr_fd(big_struct->spaced_cmd[i], cmd_lst->fd_out);
		while (big_struct->spaced_cmd[++i])
		{
			ft_putchar_fd(' ', cmd_lst->fd_out);
			ft_putstr_fd(big_struct->spaced_cmd[i], cmd_lst->fd_out);
		}
		ft_putchar_fd('\n', cmd_lst->fd_out);
	}
}
