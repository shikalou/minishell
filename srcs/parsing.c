/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <mcouppe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:37:58 by ldinaut           #+#    #+#             */
/*   Updated: 2022/08/05 15:20:10 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_spe_char_bis(char *cmd, int i)
{
	if (cmd[i + 1] && cmd[i] != cmd[i + 1])
	{
		if (cmd[i] == '|' && check_str(cmd, 0, i) == 1)
			return (NULL);
		else if (cmd[i + 1] != ' ')
			return (add_space(cmd, i));
		else if ((cmd[i + 1] == ' ')
			&& (check_str(cmd, (i + 1), ft_strlen(cmd)) == 0))
			return (cmd);
	}
	else if (cmd [i] == '<' && cmd[i + 1] == '<'
		&& (check_str(cmd, (i + 2), ft_strlen(cmd)) == 0))
		return (add_space_hereapp(cmd, i));
	else if (cmd[i] == '>' && cmd[i + 1] == '>'
		&& (check_str(cmd, (i + 2), ft_strlen(cmd)) == 0))
		return (add_space_hereapp(cmd, i));
	return (NULL);
}

char	*check_spe_char(char *cmd, int len_tmp)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '"' || cmd[i] == '\'')
			i += (ft_split_quotes(cmd, i) + 1);
		if (cmd[i] && check_char(cmd[i]) == 0)
			return (NULL);
		if (cmd[i] == '|' || cmd[i] == '>' || cmd[i] == '<')
		{
			cmd = check_spe_char_bis(cmd, i);
			if (cmd == NULL)
				return (NULL);
			if (cmd[i + 1] && cmd[i + 1] == ' ')
				i++;
		}
		if (ft_strlen(cmd) - len_tmp != 0)
		{
			i += ft_strlen(cmd) - len_tmp;
			len_tmp = ft_strlen(cmd);
		}
	}
	return (cmd);
}

int	last_parse(t_big *b, char **str, int i, int j)
{
	int		k;

	while (str && str[++i])
	{
		j = -1;
		while (str && str[i][++j])
		{
			k = j + 1;
			if (str[i][k] && ((str[i][j] == '<' && str[i][k] == '<')
				|| (str[i][j] == '>' && str[i][k] == '>')))
			{
				k++;
				while (str[i][k] && str[i][k] == ' ')
					k++;
				if (!str[i][k] || str[i][k] == '\0' || str[i][k] == '|')
					return (error_parse(b));
			}
		}
	}
	return (0);
}

int	parsing_ending(char *cmd, t_big *big_s)
{
	big_s->input = ft_sdf(cmd, '|');
	free(cmd);
	if (big_s->input[0] == NULL)
		return (0);
	if (last_parse(big_s, big_s->input, -1, -1) == 1)
		return (0);
	big_s->cmd_lst = ft_init_cmd_lst(big_s->input);
	parsing_redirection(big_s, 0);
	parsing_quotes(big_s);
	if (big_s->cmd_lst == NULL)
		return (0);
	return (1);
}

int	ft_parsing(char *cmd, t_big *big_struct)
{
	if (ft_checkquotes(cmd) != 0 || check_rafter(cmd, '>', '<', -1) == 1)
	{
		write(2, "Syntax error\n", 13);
		big_struct->status = 2;
		return (0);
	}
	cmd = check_spe_char(cmd, ft_strlen(cmd));
	if (!cmd)
	{
		free(cmd);
		write(2, "Syntax error\n", 13);
		big_struct->status = 2;
		return (0);
	}
	return (parsing_ending(cmd, big_struct));
}
