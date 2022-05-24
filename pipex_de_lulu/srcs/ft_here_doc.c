/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:54:07 by ldinaut           #+#    #+#             */
/*   Updated: 2022/03/25 14:15:03 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exec_two(t_cmd *cmd, char **argv, char **envp, int argc)
{
	pid_t	pid;

	cmd->arg_path = ft_split(argv[argc - 2], ' ');
	pid = fork();
	if (pid < 0)
		perror("fork");
	else if (pid == 0)
	{
		if (cmd->outfile != -1 && ft_find_check_path(cmd) != NULL)
		{
			free(cmd->arg_path[0]);
			cmd->arg_path[0] = ft_strdup(cmd->path);
			close(cmd->pipefd[1]);
			dup2(cmd->pipefd[0], 0);
			dup2(cmd->outfile, 1);
			execve(cmd->path, cmd->arg_path, envp);
			free(cmd->path);
		}
		ft_close(cmd, 3);
		ft_free_struct(cmd);
		exit(1);
	}
	ft_close(cmd, 3);
}

void	ft_close(t_cmd *cmd, int i)
{
	if (i == 1)
	{
		close(cmd->fd_temp);
		close(cmd->pipefd[1]);
	}
	if (i == 2)
	{
		close(cmd->infile);
		close(cmd->pipefd[1]);
	}
	if (i == 3)
	{
		if (cmd->outfile != -1)
			close(cmd->outfile);
		close(cmd->pipefd[0]);
	}
}

void	ft_dup(t_cmd *cmd)
{
	dup2(cmd->fd_temp, 0);
	dup2(cmd->pipefd[1], 1);
}

void	ft_exec_cmd(t_cmd *cmd, char **argv, char **envp)
{
	pid_t	pid;

	cmd->arg_path = ft_split(argv[3], ' ');
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
			close(cmd->pipefd[0]);
			ft_dup(cmd);
			execve(cmd->path, cmd->arg_path, envp);
			free(cmd->path);
		}
		ft_close(cmd, 1);
		ft_free_struct(cmd);
		exit(1);
	}
	ft_free_arg_path(cmd);
	ft_close(cmd, 1);
}

void	ft_here_doc(int argc, char **argv, t_cmd *cmd, char **envp)
{
	char	*line;
	int		i;

	i = -1;
	pipe(cmd->pipefd);
	cmd->outfile = open(argv[argc -1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (cmd->outfile == -1)
		ft_printf("%s : %s\n", strerror(errno), argv[argc - 1]);
	cmd->limiter = (ft_strjoin(argv[2], "\n"));
	line = get_next_line(0);
	while (ft_memcmp(line, cmd->limiter, ft_strlen(line)) != 0)
	{
		write(cmd->pipefd[1], line, (int)ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	free(cmd->limiter);
	free(line);
	close(cmd->pipefd[1]);
	ft_exec_cmd(cmd, argv, envp);
	while (++i < argc - 6)
		ft_exec_middle(cmd, argv[i + 4], envp);
	ft_exec_two(cmd, argv, envp, argc);
	ft_wait(argc - 4);
	ft_exit(cmd);
}
