/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:44:56 by ldinaut           #+#    #+#             */
/*   Updated: 2022/07/07 20:36:37 by ldinaut          ###   ########.fr       */
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
	if (i == 2)
	{
		static_struct->spaced_par = NULL;
		ft_free_tab(static_struct->spaced_par);
		ft_lstclear_cmd(static_struct->cmd_lst);
	}
}

void	sig_handler_heredoc(int intSig)
{
	if (intSig == SIGINT)
	{
		get_value(NULL, 2);
		//ft_putchar_fd('\n', 1);
		exit (0);
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
