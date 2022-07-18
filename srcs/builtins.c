/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:12:57 by ldinaut           #+#    #+#             */
/*   Updated: 2022/07/18 15:56:13 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_big_struct *big_struct, t_cmd_lst *cmd_lst)
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

int	ft_env(t_big_struct *big_s, t_cmd_lst *cmd_lst)
{
	char	**env;
	int		i;

	env = big_s->envp;
	i = 0;
	while (env[i] != NULL)
	{
		if (env[i] != NULL && env[i][0] && ft_strchr(env[i], '=') != 0)
			ft_putendl_fd(env[i], cmd_lst->fd_out);
		i++;
	}
	return (1);
}

//		norme to-dos :
// voir comment on peut update les big_s->status direct
//	ds les fonc pr return 1 pour la norme
// pareil pr ft_pwd sense return un int mais sans ke son retour soit check
int	ft_check_builtin_multi(t_big_struct *big_s, t_cmd_lst *cmd_lst)
{
	if (cmd_lst->command && ft_strcmp(big_s->spaced_cmd[0], "pwd") == 0)
		return (ft_pwd(big_s, cmd_lst));
	else if (cmd_lst->command && ft_strcmp(big_s->spaced_cmd[0], "echo") == 0)
		return (ft_echo(big_s, cmd_lst));
	else if (cmd_lst->command && ft_strcmp(big_s->spaced_cmd[0], "cd") == 0)
		return (big_s->status = ft_cd(big_s));
	else if (cmd_lst->command && ft_strcmp(big_s->spaced_cmd[0], "export") == 0)
		return (ft_export(big_s, cmd_lst));
	else if (cmd_lst->command && ft_strcmp(big_s->spaced_cmd[0], "exit") == 0)
	{
		ft_exit(big_s);
		return (1);
	}
	else if (cmd_lst->command && ft_strcmp(big_s->spaced_cmd[0], "env") == 0)
		return (ft_env(big_s, cmd_lst));
	else if (cmd_lst->command && ft_strcmp(big_s->spaced_cmd[0], "unset") == 0)
		return (ft_unset(big_s, cmd_lst));
	return (0);
}
