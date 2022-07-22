/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:12:57 by ldinaut           #+#    #+#             */
/*   Updated: 2022/07/22 11:49:09 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_big *big_struct, t_cmd_lst *cmd_lst)
{
	if (big_struct->absolut_path != NULL)
	{
		free(big_struct->absolut_path);
		big_struct->absolut_path = NULL;
	}
	big_struct->absolut_path = getcwd(NULL, 0);
	if (!big_struct->absolut_path)
	{
		perror("getcwd");
		return (1);
	}
	ft_putendl_fd(big_struct->absolut_path, cmd_lst->fd_out);
	big_struct->status = 0;
	return (1);
}

int	ft_env(t_big *b, t_cmd_lst *cmd_lst)
{
	int		i;

	if (b->spaced_cmd[1] != NULL)
	{
		ft_putendl_fd("env: too many arguments", 2);
		b->status = 2;
		return (1);
	}
	i = 0;
	printf("dans env %d\n", cmd_lst->fd_out);
	while (b->envp && b->envp[i])
	{
		if (b->envp[i] != NULL && b->envp[i][0] && ft_strchr(b->envp[i], '=') != 0)
			ft_putendl_fd(b->envp[i], cmd_lst->fd_out);
		i++;
	}
	b->status = 0;
	return (1);
}

int	ft_check_builtin_multi(t_big *b, t_cmd_lst *cmd_lst)
{
	if (b->spaced_cmd[0])
	{
		if (cmd_lst->command && ft_strcmp(b->spaced_cmd[0], "pwd") == 0)
			return (ft_pwd(b, cmd_lst));
		else if (cmd_lst->command && ft_strcmp(b->spaced_cmd[0], "echo") == 0)
			return (ft_echo(b, cmd_lst));
		else if (cmd_lst->command && ft_strcmp(b->spaced_cmd[0], "cd") == 0)
			return (ft_cd(b));
		else if (cmd_lst->command && ft_strcmp(b->spaced_cmd[0], "export") == 0)
			return (ft_export(b, cmd_lst));
		else if (cmd_lst->command && ft_strcmp(b->spaced_cmd[0], "exit") == 0)
		{
			ft_exit(b);
			return (1);
		}
		else if (cmd_lst->command && ft_strcmp(b->spaced_cmd[0], "env") == 0)
			return (ft_env(b, cmd_lst));
		else if (cmd_lst->command && ft_strcmp(b->spaced_cmd[0], "unset") == 0)
			return (ft_unset(b, cmd_lst));
	}
	return (0);
}
