/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:12:57 by ldinaut           #+#    #+#             */
/*   Updated: 2022/06/22 17:10:59 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_big_struct *big_struct, t_cmd_lst *cmd_lst)
{
	big_struct->absolut_path = getcwd(NULL, 0);
	if (!big_struct->absolut_path)
	{
		perror("getcwd");
		return ;
	}
	ft_putendl_fd(big_struct->absolut_path, cmd_lst->fd_out);
}
