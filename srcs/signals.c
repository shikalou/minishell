/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:44:56 by ldinaut           #+#    #+#             */
/*   Updated: 2022/06/27 15:10:00 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int intSig)
{
	if (intSig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_handler_cmd(int intSig)
{
	if (intSig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
	}
}
