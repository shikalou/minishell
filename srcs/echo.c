/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:11:10 by ldinaut           #+#    #+#             */
/*   Updated: 2022/08/04 15:26:21 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_echo_n(char *s)
{
	int	i;

	i = 1;
	if (!s)
		return (0);
	if (ft_memcmp(s, "-n", 2))
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
	(void)len;
	if (ft_strncmp(spaced, " \"\"", 2) == 0
		|| ft_strncmp(spaced, " ''", 2) == 0)
	{
		ft_putchar_fd(' ', cmd_lst->fd_out);
		return (1);
	}
	ft_putstr_fd(spaced, cmd_lst->fd_out);
	return (0);
}

void	echo_putstr(t_big *big_s, t_cmd_lst *cmd_lst, int i)
{
	int	len;
	int	check;

	while (big_s->spaced_cmd[i])
	{
		check = 0;
		len = ft_strlen(big_s->spaced_cmd[i]);
		if (echo_check_sp_dq(big_s, i) == 1)
		{
			printf("Coucou\n");
			check = 1;
			ft_putstr_fd(" ", cmd_lst->fd_out);
			i++;
		}
		else if (echo_check_sp_dq(big_s,i) == 2
			|| ft_strncmp(big_s->spaced_cmd[i], "\"\"", len) == 0
			|| ft_strncmp(big_s->spaced_cmd[i], "''", len) == 0)
		{
			check = 1;
			i++ ;
		}
		else
			ft_putstr_fd(big_s->spaced_cmd[i++], cmd_lst->fd_out);
		if (check == 0)
			ft_putstr_fd(" ", cmd_lst->fd_out);
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
				printf("1tmp before trim = %s\n", tmp);
				sp[i] = strtrim_aug(tmp, 0);
			//	free(tmp);
				break ;
			}
			else if (sp[i][j + 1] && sp[i][j + 2]  && (i == 1) && ((sp[i][j] == '"' && sp[i][j + 1] == '"')
				|| (sp[i][j] == '\'' && sp[i][j + 1] == '\'')))
			{
				tmp = ft_strdup(sp[i]);
				free(sp[i]);
				printf("2tmp before trim = %s\n", tmp);
				sp[i] = ft_strtrim(tmp, "\"\"");
				free(tmp);
				break ;
			}
			if (sp[i][j] == '\'' || sp[i][j] == '"')
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
			echo_putstr(big_s, cmd_lst, i);
			big_s->status = 0;
			return (1);
		}
	}
	if (big_s->spaced_cmd[i])
	{
		ft_parsing_echo(big_s->spaced_cmd, 0, 0);
		echo_putstr(big_s, cmd_lst, i);
		ft_putchar_fd('\n', cmd_lst->fd_out);
	}
	else
		ft_putchar_fd('\n', cmd_lst->fd_out);
	big_s->status = 0;
	return (1);
}
