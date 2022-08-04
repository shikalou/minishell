/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <mcouppe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:11:10 by ldinaut           #+#    #+#             */
/*   Updated: 2022/08/04 19:47:07 by mcouppe          ###   ########.fr       */
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
	//int	len;
	int	check;

	check = 0;
	while (big_s->spaced_cmd[i])
	{
		//printf("dans echo_putstr ->%s<-\n", big_s->spaced_cmd[i]);
		//len = ft_strlen(big_s->spaced_cmd[i]);
		if (((ft_strcmp(big_s->spaced_cmd[i], "''") == 0) || (ft_strcmp(big_s->spaced_cmd[i], "\"\"") == 0))
			|| (big_s->spaced_cmd[i + 1] && (ft_strcmp(big_s->spaced_cmd[i + 1], "''") == 0
			|| ft_strcmp(big_s->spaced_cmd[i + 1], "\"\"") == 0)))
		{
		//	printf("Coucou\n");
		//	ft_putstr_fd(" ", cmd_lst->fd_out);
			check = 1;
		}
		if ((ft_strchr(big_s->spaced_cmd[i], '"') == 0)
				|| (ft_strchr(big_s->spaced_cmd[i], '"') == 0))
			ft_putstr_fd(big_s->spaced_cmd[i], cmd_lst->fd_out);
	//	printf("check ?? %d\n", check);
		if (check == 0 && big_s->spaced_cmd[i + 1])
		{
	//		printf("tu te fous de ma gueule shellmini check=%d\n", check);
			ft_putstr_fd(" ", cmd_lst->fd_out);
		}
		check = 0;
		i++;
	}
}

void	ft_parsing_echo(t_big *b, int i, int j)
{
	char	*tmp;

	(void)j;
	while (b->spaced_cmd[++i])
	{
		if (ft_strchr(b->spaced_cmd[i], '\'') || ft_strchr(b->spaced_cmd[i], '"'))
		{
			if ((ft_strcmp(b->spaced_cmd[i], "\"\"") == 0) || (ft_strcmp(b->spaced_cmd[i], "''") == 0))
				;
			else
			{
				tmp = ft_strdup(b->spaced_cmd[i]);
				free(b->spaced_cmd[i]);
				b->spaced_cmd[i] = strtrim_aug(tmp, 0);
			}
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
			ft_parsing_echo(big_s, 0, 0);
			echo_putstr(big_s, cmd_lst, i);
			big_s->status = 0;
			return (1);
		}
	}
	if (big_s->spaced_cmd[i])
	{
		ft_parsing_echo(big_s, 0, 0);
		echo_putstr(big_s, cmd_lst, i);
		ft_putchar_fd('\n', cmd_lst->fd_out);
	}
	else
		ft_putchar_fd('\n', cmd_lst->fd_out);
	big_s->status = 0;
	return (1);
}
