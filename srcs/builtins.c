/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:12:57 by ldinaut           #+#    #+#             */
/*   Updated: 2022/07/14 15:33:49 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_big_struct *big_struct, t_cmd_lst *cmd_lst)
{
	big_struct->absolut_path = getcwd(NULL, 0);
	if (!big_struct->absolut_path)
	{
		perror("getcwd");
		return (1);
	}
	ft_putendl_fd(big_struct->absolut_path, cmd_lst->fd_out);
	return (0);
}

int	ft_env(t_big_struct *big_s, t_cmd_lst *cmd_lst)
{
	t_env_lst	*env;

	env = big_s->env_lst;
	while (env != NULL)
	{
		if (env->line != NULL && env->line[0] && ft_strchr(env->line, '=') != 0)
			ft_putendl_fd(env->line, cmd_lst->fd_out);
		env = env->next;
	}
	return (1);
}

int	ft_check_builtin_multi(t_big_struct *big_struct, t_cmd_lst *cmd_lst)
{
	if (cmd_lst->command && ft_strcmp(big_struct->spaced_cmd[0], "pwd") == 0)
	{
		ft_pwd(big_struct, cmd_lst);
		return (1);
	}
	else if (cmd_lst->command && ft_strcmp(big_struct->spaced_cmd[0], "echo") == 0)
	{
		big_struct->status = ft_echo(big_struct, cmd_lst);
		return (1);
	}
	else if (cmd_lst->command && ft_strcmp(big_struct->spaced_cmd[0], "cd") == 0)
	{
		big_struct->status = ft_cd(big_struct, cmd_lst);
		return (1);
	}
	else if (cmd_lst->command && ft_strcmp(big_struct->spaced_cmd[0], "export") == 0)
		return (ft_export(big_struct, cmd_lst));
	else if (cmd_lst->command && ft_strcmp(big_struct->spaced_cmd[0], "exit") == 0)
	{
		ft_exit(big_struct);
		return (1);
	}
	else if (cmd_lst->command && ft_strcmp(big_struct->spaced_cmd[0], "env") == 0)
		return(ft_env(big_struct, cmd_lst));
	else if (cmd_lst->command && ft_strcmp(big_struct->spaced_cmd[0], "unset") == 0)
		return (ft_unset(big_struct, cmd_lst));
	return (0);
}
