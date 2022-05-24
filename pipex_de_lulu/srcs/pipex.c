/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 15:11:09 by ldinaut           #+#    #+#             */
/*   Updated: 2022/03/21 20:27:55 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exec_last(t_cmd *cmd, char *argv, char **envp)
{
	pid_t	pid;

	cmd->arg_path = ft_split(argv, ' ');
	pid = fork();
	if (pid < 0)
		perror("fork");
	else if (pid == 0)
	{
		if (cmd->outfile != -1 && ft_find_check_path(cmd) != NULL )
		{
			free(cmd->arg_path[0]);
			cmd->arg_path[0] = ft_strdup(cmd->path);
			dup2(cmd->pipefd[0], 0);
			dup2(cmd->outfile, 1);
			execve(cmd->path, cmd->arg_path, envp);
			free(cmd->path);
			close(cmd->outfile);
		}
		ft_free_struct(cmd);
		exit(1);
	}
	if (cmd->outfile != -1)
		close(cmd->outfile);
	close(cmd->pipefd[0]);
}

void	ft_exec_middle(t_cmd *cmd, char *argv, char **envp)
{
	pid_t	pid;

	cmd->arg_path = ft_split(argv, ' ');
	cmd->fd_temp = cmd->pipefd[0];
	pipe(cmd->pipefd);
	pid = fork();
	if (pid < 0)
		perror("fork");
	else if (pid == 0)
	{
		if (ft_find_check_path(cmd) != NULL)
		{
			free(cmd->arg_path[0]);
			cmd->arg_path[0] = ft_strdup(cmd->path);
			dup2(cmd->fd_temp, 0);
			close(cmd->pipefd[0]);
			dup2(cmd->pipefd[1], 1);
			execve(cmd->path, cmd->arg_path, envp);
			free(cmd->path);
		}
		ft_free_struct(cmd);
		exit(1);
	}
	ft_free_arg_path(cmd);
	ft_close(cmd, 1);
}

void	ft_exec_one(t_cmd *cmd, char **argv, char **envp)
{
	pid_t	pid;

	cmd->arg_path = ft_split(argv[2], ' ');
	pid = fork();
	if (pid < 0)
		perror("fork");
	else if (pid == 0)
	{
		if (ft_find_check_path(cmd) != NULL)
		{
			free(cmd->arg_path[0]);
			cmd->arg_path[0] = ft_strdup(cmd->path);
			dup2(cmd->infile, 0);
			close(cmd->pipefd[0]);
			dup2(cmd->pipefd[1], 1);
			execve(cmd->path, cmd->arg_path, envp);
			free(cmd->path);
		}
		ft_close(cmd, 2);
		ft_free_struct(cmd);
		exit(1);
	}
	ft_free_arg_path(cmd);
	ft_close(cmd, 2);
}

void	ft_wait(int argc)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		wait(NULL);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;
	int		i;

	if (argc > 4)
	{
		i = -1;
		cmd = ft_init_struct(envp);
		if (!cmd)
			return (1);
		if (ft_memcmp(argv[1], "here_doc", 9) == 0)
			ft_here_doc(argc, argv, cmd, envp);
		pipe(cmd->pipefd);
		if (ft_open(cmd, argv, argc) == 0)
			ft_exec_one(cmd, argv, envp);
		else
			close(cmd->pipefd[1]);
		while (++i < argc - 5)
			ft_exec_middle(cmd, argv[i + 3], envp);
		ft_exec_last(cmd, argv[i + 3], envp);
		ft_wait(argc - 3);
		ft_free_struct(cmd);
		return (0);
	}
	ft_printf("Error\nTry [infile] [cmd1] [cmd2] ... [cmdn] [outfile]\n");
	return (1);
}
