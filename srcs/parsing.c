/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:37:58 by ldinaut           #+#    #+#             */
/*   Updated: 2022/06/15 17:54:34 by ldinaut          ###   ########.fr       */
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
		{
			i += (ft_split_quotes(cmd, i) + 1);
		}
		if (cmd[i] && check_char(cmd[i]) == 0)
		{
			printf("check 1\n");
			return (NULL);
		}
		if (cmd[i] == '|' || cmd[i] == '>' || cmd[i] == '<')
		{
			if (cmd[i] != cmd[i + 1])
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
	int	check_s;
	int	check_d;

	i = -1;
	check_s = 0;
	check_d = 0;
	while (cmd[++i])
	{
		if (cmd[i] && cmd[i] == '\'')
		{
			while (cmd[i] && cmd[++i] && cmd[i] != '\'')
				;
			if (!cmd[i])
				check_s++;
		}
		if (cmd[i] && cmd[i] == '\"')
		{
			while (cmd[i] && cmd[++i] && cmd[i] != '\"')
				;
			if (!cmd[i])
				check_d++;
		}
	}
	return (check_d + check_s);
}

int	ft_parsing(char *cmd, t_big_struct *big_struct)
{
	if (ft_checkquotes(cmd) != 0)
	{
		write(2, "Error syntax\n", 13);
		return (0);
	}
	cmd = check_spe_char(cmd);
	if (!cmd)
	{
		write(2, "Error syntax\n", 13);
		return (0);
	}
	big_struct->input = ft_split_du_futur(cmd, '|');
	if (big_struct->input[0] == NULL)
		return (0);
	big_struct->cmd_lst = ft_init_cmd_lst(big_struct->input);
	parsing_quotes(big_struct);
	//parsing_redirection(big_struct);
	return (1);
}
