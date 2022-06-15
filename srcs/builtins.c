/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:12:57 by ldinaut           #+#    #+#             */
/*   Updated: 2022/06/15 13:44:28 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_big_struct *big_struct, char *command)
{
	//	utiliser putstr_fd pour les redirections
	(void)command;
	printf("%s\n", big_struct->absolut_path);
	//	putstr_fd(big_struct->absolut_path, head->fd_out);
}


void	ft_echo(t_big_struct *big_struct, char *command)
{
	// utiliser putstr_fd pour les redirections
	(void)big_struct;
	printf("%s\n", (command + 5));
}
