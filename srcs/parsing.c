/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:37:58 by ldinaut           #+#    #+#             */
/*   Updated: 2022/06/02 15:46:55 by mcouppe          ###   ########.fr       */
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
			i += ft_split_quotes(cmd, i);
		if (cmd[i] == '|' || cmd[i] == '>' || cmd[i] == '<')
		{
			if (cmd[i] != cmd[i + 1])
			{
				if (cmd[i] == '|' && charisalpha_aug(cmd, 0, i) == 1)
					return (NULL);
				else if (cmd[i + 1] != ' ')
					cmd = add_space(cmd, i);
				else if ((cmd[i + 1] == ' ') && (charisalpha_aug(cmd, (i + 1), ft_strlen(cmd)) == 0))
					i++;
				else if ((cmd[i + 1] = ' ') || (charisalpha_aug(cmd, (i + 1), ft_strlen(cmd)) == 1))
					return (NULL);
			}
			else if (cmd[i] == '<' && cmd[i + 1] == '<' && (charisalphaorspace(cmd[i + 2]) == 1))
				cmd = add_space_hereapp(cmd, i);
			else if (cmd[i] == '>' && cmd[i + 1] == '>' && (charisalphaorspace(cmd[i + 2]) == 1))
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
		if (cmd[i] &&cmd[i] == '\'')
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
	int		i;

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
	i = 0;
	while (big_struct->input[i])
	{
		printf("%s\n", big_struct->input[i]);
		i++;
	}
	big_struct->cmd_lst = ft_init_cmd_lst(big_struct->input);
	return (1);
}
