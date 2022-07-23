/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:11:10 by ldinaut           #+#    #+#             */
/*   Updated: 2022/07/23 20:18:51 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_echo_n(char *s)
{
	int	i;

	i = 1;
	if (!s)
		return (0);
	while (s && s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	check_echo_putstr(char *spaced, t_cmd_lst *cmd_lst, int len)
{
	if (ft_strncmp(spaced, "\"\"", len) == 0
		|| ft_strncmp(spaced, "''", len) == 0)
	{
		ft_putchar_fd(' ', cmd_lst->fd_out);
		return (1);
	}
	ft_putstr_fd(spaced, cmd_lst->fd_out);
	return (0);
}

void	echo_putstr(t_big *big_s, t_cmd_lst *cmd_lst, int i, int check)
{
	int	len;

	len = ft_strlen(big_s->spaced_cmd[i]);
	check += check_echo_putstr(big_s->spaced_cmd[i], cmd_lst, len);
	while (big_s->spaced_cmd[i] && big_s->spaced_cmd[++i])
	{
		len = ft_strlen(big_s->spaced_cmd[i]);
		if (ft_strncmp(big_s->spaced_cmd[i], "\"\"", len) == 0
			|| ft_strncmp(big_s->spaced_cmd[i], "''", len) == 0)
		{
			ft_putstr_fd(" ", cmd_lst->fd_out);
			check++;
		}
		else
		{
			if (check == 0)
				ft_putchar_fd(' ', cmd_lst->fd_out);
			else
				check--;
			ft_putstr_fd(big_s->spaced_cmd[i], cmd_lst->fd_out);
		}
	}
}

void	ft_parsing_echo(char **sp, int i, int j)
{
	char	*tmp;

	while (sp[++i])
	{
		j = 0;
		while (sp[i][j])
		{
			if (sp[i][j + 1] && ((sp[i][j] == '"' && sp[i][j + 1] != '"')
				|| (sp[i][j] == '\'' && sp[i][j + 1] != '\'')))
			{
				tmp = ft_strdup(sp[i]);
				free(sp[i]);
				if (tmp[j] == '"')
					sp[i] = ft_strtrim(tmp, "\"");
				else
					sp[i] = ft_strtrim(tmp, "\'");
				free(tmp);
				break ;
			}
			else if (sp[i][j] == '\'' || sp[i][j] == '"')
				j += 2;
			else
				j++;
		}
	}
}

int	ft_echo(t_big *big_s, t_cmd_lst *cmd_lst)
{
	int	i;

	i = 1;
	if (big_s->spaced_cmd[i] && ft_memcmp(big_s->spaced_cmd[i], "-n", 2) == 0)
	{
		if (ft_check_echo_n(big_s->spaced_cmd[i]))
		{
			while (ft_check_echo_n(big_s->spaced_cmd[i]))
				i++;
			ft_parsing_echo(big_s->spaced_cmd, 0, 0);
			echo_putstr(big_s, cmd_lst, i, 0);
			big_s->status = 0;
			return (1);
		}
	}
	if (big_s->spaced_cmd[i])
	{
		ft_parsing_echo(big_s->spaced_cmd, 0, 0);
		echo_putstr(big_s, cmd_lst, i, 0);
		ft_putchar_fd('\n', cmd_lst->fd_out);
	}
	else
		ft_putchar_fd('\n', cmd_lst->fd_out);
	big_s->status = 0;
	return (1);
}
