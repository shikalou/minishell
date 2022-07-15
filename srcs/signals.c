/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:44:56 by ldinaut           #+#    #+#             */
/*   Updated: 2022/07/15 22:03:45 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_value(t_big_struct *big_struct, t_cmd_lst *cmd_lst, int i)
{
	static t_big_struct	*static_struct;
	static t_cmd_lst	*static_cmd_lst;

	if (i == 0)
	{
		static_struct = big_struct;
		static_cmd_lst = cmd_lst;
	}
	if (i == 1)
	{
		static_struct->status = 130;
	}
	if (i == 2)
	{
		close(static_cmd_lst->fd_in);
		ft_free_child(static_struct, 0);
		// ft_free_tab(static_struct->spaced_par);
		// ft_lstclear_cmd(static_struct->cmd_lst);
		// ft_lstclear_env(static_struct->env_lst);
	}
}

void	sig_handler_heredoc(int intSig)
{
	if (intSig == SIGINT)
	{
		get_value(NULL, NULL, 2);
		exit(2);
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
		get_value(NULL, NULL, 1);
	}
}

void	sig_handler_cmd(int intSig)
{
	if (intSig == SIGQUIT)
	{
		exit(3);
	}
}
