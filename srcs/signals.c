/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:44:56 by ldinaut           #+#    #+#             */
/*   Updated: 2022/07/06 14:49:50 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_value(t_big_struct *big_struct, int i)
{
	static t_big_struct *static_struct;

	if (i == 0)
		static_struct = big_struct;
	if (i == 1)
	{
		static_struct->status = 130;
	}
}

void	sig_handler_heredoc(int intSig)
{
	if (intSig == SIGINT)
	{

	}
}

void	sig_handler(int intSig)
{
	if (intSig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		get_value(NULL, 1);
	}
}

void	sig_handler_cmd(int intSig)
{
	if (intSig == SIGQUIT)
	{
		exit (3);
	}
}
