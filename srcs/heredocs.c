/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 15:29:57 by ldinaut           #+#    #+#             */
/*   Updated: 2022/07/04 17:58:50 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//void	ft_open_heredoc(t_big_struct *big_struct)

void	ft_heredoc(t_big_struct *big_struct, t_cmd_lst *cmd_lst, int i)
{
	char	*input;
	char	*new;

	if (cmd_lst->fd_in != 0)
		close(cmd_lst->fd_in);
	cmd_lst->fd_in = open("temp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	input = readline("> ");
	while (ft_strcmp(input, big_struct->spaced_par[i]) != 0)
	{
		new = ft_strjoin(input, "\n");
		free(input);
		write(cmd_lst->fd_in, new, ft_strlen(new));
		free(new);
		input = readline("> ");
	}
	close(cmd_lst->fd_in);
	cmd_lst->fd_in = open("temp", O_RDONLY);
}
