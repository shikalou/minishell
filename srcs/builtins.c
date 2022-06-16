/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:12:57 by ldinaut           #+#    #+#             */
/*   Updated: 2022/06/16 18:29:23 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_big_struct *big_struct, t_cmd_lst *cmd_lst)
{
	ft_putstr_fd(big_struct->absolut_path, cmd_lst->fd_out);
}


void	ft_echo(t_big_struct *big_struct, t_cmd_lst *cmd_lst)
{
	(void)big_struct;
	ft_putendl_fd(cmd_lst->command + 5, cmd_lst->fd_out);
}
