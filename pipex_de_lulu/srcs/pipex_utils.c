/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:59:04 by ldinaut           #+#    #+#             */
/*   Updated: 2022/03/21 21:41:48 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_check_slash(t_cmd *cmd)
{
	if (access(cmd->arg_path[0], X_OK) == 0)
	{
		cmd->path = ft_strdup(cmd->arg_path[0]);
		return (cmd->path);
	}
	ft_printf("%s: %s\n", strerror(errno), cmd->arg_path[0]);
	return (NULL);
}

char	*ft_find_check_path(t_cmd *cmd)
{
	int		i;
	char	*temp;

	i = 0;
	if (ft_strchr(cmd->arg_path[0], '/'))
		return (ft_check_slash(cmd));
	else
	{
		while (cmd->path_tab[i] != NULL)
		{
			temp = ft_strjoin(cmd->path_tab[i], "/");
			cmd->path = ft_strjoin(temp, cmd->arg_path[0]);
			free(temp);
			if (cmd->path && access(cmd->path, X_OK) == 0)
				return (cmd->path);
			i++;
			free(cmd->path);
		}
		ft_printf("command not found: %s\n", cmd->arg_path[0]);
		return (NULL);
	}
}

char	*ft_find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_memcmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

int	ft_open(t_cmd *cmd, char **argv, int argc)
{
	int	i;

	i = 0;
	cmd->infile = open(argv[1], O_RDONLY);
	if (cmd->infile == -1)
	{
		ft_printf("%s: %s\n", strerror(errno), argv[1]);
		i++;
	}
	cmd->outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (cmd->outfile == -1)
		ft_printf("%s : %s\n", strerror(errno), argv[argc - 1]);
	return (i);
}

t_cmd	*ft_init_struct(char **envp)
{
	t_cmd	*cmd;
	char	*env;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	env = ft_find_path(envp);
	cmd->path_tab = ft_split(env, ':');
	cmd->path = NULL;
	cmd->arg_path = NULL;
	return (cmd);
}
