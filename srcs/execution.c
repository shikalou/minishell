/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:22:19 by ldinaut           #+#    #+#             */
/*   Updated: 2022/07/21 13:52:03 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	petit probleme ici (lol on adore)

	on dit que spaced_cmd = ft_split sauf que ft_split skip pas les cot
	du coup il faut appeler sdf
	mais sdf il critche bcp :'((
	parce que sinn echo "l            o           l"
	donne --> l o l
	:'((((
	ou alors on fait juste echo avec cmd_lst->command
*/
int	ft_simple_exec(t_big *big_s, t_cmd_lst *cmd_lst)
{
	malloc_spacedcmd_simple(big_s);
	if (big_s->spaced_cmd[0] == NULL)
		return (1);
	if (ft_check_builtin_multi(big_s, cmd_lst) == 0)
	{
		cmd_lst->pid = fork();
		if (cmd_lst->pid == 0)
		{
			if (ft_find_check_path(big_s, big_s->spaced_cmd) != NULL)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, sig_handler_cmd);
				ft_dup(cmd_lst);
				execve(big_s->cmd_updated, big_s->spaced_cmd, big_s->envp);
				perror("execve");
			}
			ft_free_tab(big_s->spaced_cmd);
			ft_free_child(big_s, 0);
			exit(127);
		}
	}
	else
		return (1);
	ft_close_fdinout(cmd_lst);
	return (0);
}

void	ft_exec(t_big *big_struct)
{
	t_cmd_lst	*cmd_lst;

	cmd_lst = big_struct->cmd_lst;
	signal(SIGINT, SIG_IGN);
	if (cmd_lst && !cmd_lst->next)
	{
		if (ft_simple_exec(big_struct, cmd_lst) == 0)
		{
			waitpid(cmd_lst->pid, &big_struct->status, 0);
			if (WIFSIGNALED(big_struct->status))
			{
				big_struct->status = (WTERMSIG(big_struct->status) + 128);
				ft_check_signal(big_struct->status);
			}
			else
				big_struct->status = WEXITSTATUS(big_struct->status);
		}
	}
	else if (cmd_lst && cmd_lst->next)
		ft_multi_pipe(big_struct);
	signal(SIGINT, sig_handler);
}
