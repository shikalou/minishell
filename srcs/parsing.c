/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:37:58 by ldinaut           #+#    #+#             */
/*   Updated: 2022/07/19 11:48:07 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_spe_char(char *cmd)
{
	int	i;
	int	len_tmp;

	i = -1;
	len_tmp = ft_strlen(cmd);
	while (cmd[++i])
	{
		if (cmd[i] == '"' || cmd[i] == '\'')
			i += (ft_split_quotes(cmd, i) + 1);
		if (cmd[i] && check_char(cmd[i]) == 0)
			return (NULL);
		if (cmd[i] == '|' || cmd[i] == '>' || cmd[i] == '<')
		{
			if (cmd[i + 1] && cmd[i] != cmd[i + 1])
			{
				if (cmd[i] == '|' && check_str(cmd, 0, i) == 1)
					return (NULL);
				else if (cmd[i + 1] != ' ')
					cmd = add_space(cmd, i);
				else if ((cmd[i + 1] == ' ')
					&& (check_str(cmd, (i + 1), ft_strlen(cmd)) == 0))
					i++;
			}
			else if (cmd[i] == '<' && cmd[i + 1] == '<'
				&& (check_str(cmd, (i + 2), ft_strlen(cmd)) == 0))
				cmd = add_space_hereapp(cmd, i);
			else if (cmd[i] == '>' && cmd[i + 1] == '>'
				&& (check_str(cmd, (i + 2), ft_strlen(cmd)) == 0))
					cmd = add_space_hereapp(cmd, i);
			else
				return (NULL);
		}
		if (ft_strlen(cmd) - len_tmp != 0)
		{
			i += ft_strlen(cmd) - len_tmp;
			len_tmp = ft_strlen(cmd);
		}
	}
	return (cmd);
}

int	ft_checkquotes(char *cmd)
{
	int	i;

	i = -1;
	while (cmd && cmd[++i])
	{
		if (cmd[i] && cmd[i] == '\'')
		{
			while (cmd[i] && cmd[++i] && cmd[i] != '\'')
				;
			if (!cmd[i])
				return (1);
		}
		if (cmd[i] && cmd[i] == '\"')
		{
			while (cmd[i] && cmd[++i] && cmd[i] != '\"')
				;
			if (!cmd[i])
				return (1);
		}
	}
	return (0);
}

int	check_after_pipe(char *cmd, char c)
{
	int	j;
	int	i;

	if (!cmd)
		return (1);
	i = 0;
	j = 0;
	while (cmd && cmd[i] && cmd[i] != '\0')
	{
		if (cmd[i] == c)
		{
			i++;
			j = 0;
			while (cmd && cmd[i] && cmd[i] != '\0')
			{
				if (cmd[i] != '\0' && ft_isalnum(cmd[i]) == 1)
					j++;
				i++;
			}
			if (j == 0)
				return (1);
			else
				i = (i - j) - 1;
		}
		i++;
	}
	return (0);
}

int	ft_parsing(char *cmd, t_big_struct *big_struct)
{
	if (ft_checkquotes(cmd) != 0)
	{
		write(2, "Error syntax\n", 13);
		big_struct->status = 2;
		return (0);
	}
	cmd = check_spe_char(cmd);
	if (!cmd || (check_after_pipe(cmd, '|') == 1
			|| check_after_pipe(cmd, '<') == 1
			|| check_after_pipe(cmd, '>') == 1))
	{
		free(cmd);
		write(2, "Error syntax\n", 13);
		big_struct->status = 2;
		return (0);
	}
	big_struct->input = ft_split_du_futur(cmd, '|');
	free(cmd);
	if (big_struct->input[0] == NULL)
		return (0);
	big_struct->cmd_lst = ft_init_cmd_lst(big_struct->input);
	parsing_quotes(big_struct);
	parsing_redirection(big_struct);
	if (big_struct->cmd_lst == NULL)
		return (0);
	return (1);
}
