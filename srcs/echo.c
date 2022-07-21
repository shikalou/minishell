/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:11:10 by ldinaut           #+#    #+#             */
/*   Updated: 2022/07/21 17:20:23 by mcouppe          ###   ########.fr       */
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

void	echo_putstr(t_big *big_s, t_cmd_lst *cmd_lst, int i, int check)
{
	int	len;

	len = ft_strlen(big_s->spaced_cmd[i]);
	if (ft_strncmp(big_s->spaced_cmd[i], "\"\"", len) == 0
		|| ft_strncmp(big_s->spaced_cmd[i], "''", len) == 0)
			ft_putchar_fd(' ', cmd_lst->fd_out);
	else
		ft_putstr_fd(big_s->spaced_cmd[i], cmd_lst->fd_out);
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

void	ft_parsing_echo(t_big *b)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	i = 1;
	while (b->spaced_cmd[i])
	{
		j = 0;
	//	printf("c bizar ou pas\n %s\n", b->spaced_cmd[i]);
		while (b->spaced_cmd[i][j])
		{
			k = j + 1;
			if (b->spaced_cmd[i][j] == '"' && b->spaced_cmd[i][k]
				&& b->spaced_cmd[i][k] != '"')
			{
				tmp = ft_strdup(b->spaced_cmd[i]);
				free(b->spaced_cmd[i]);
				b->spaced_cmd[i] = ft_strtrim(tmp, "\"");
				free(tmp);
				break;
			}
			else if (b->spaced_cmd[i][j] == '\'' && b->spaced_cmd[i][k]
				&& b->spaced_cmd[i][k] != '\'')
			{
				tmp = ft_strdup(b->spaced_cmd[i]);
				free(b->spaced_cmd[i]);
				b->spaced_cmd[i] = ft_strtrim(tmp, "\'");
				free(tmp);
				break;
			}
			else if (b->spaced_cmd[i][j] == '\'')
				j += 2;
			else if (b->spaced_cmd[i][j] == '"')
				j += 2;
			else
				j++;
		}
	//	printf("c ici ou pas\n %s\n", b->spaced_cmd[i]);
		i++;
	}
//	printf("c normal ou pas\n %s\n", b->spaced_cmd[i]);
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
			ft_parsing_echo(big_s);
			echo_putstr(big_s, cmd_lst, i, 0);
			big_s->status = 0;
			return (1);
		}
	}
	if (big_s->spaced_cmd[i])
	{
		ft_parsing_echo(big_s);
		echo_putstr(big_s, cmd_lst, i, 0);
		ft_putchar_fd('\n', cmd_lst->fd_out);
	}
	else
		ft_putchar_fd('\n', cmd_lst->fd_out);
	big_s->status = 0;
	return (1);
}
