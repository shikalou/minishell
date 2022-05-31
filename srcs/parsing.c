/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:37:58 by ldinaut           #+#    #+#             */
/*   Updated: 2022/05/31 17:14:59 by ldinaut          ###   ########.fr       */
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
		if (cmd[i] == '"')
		{
			while (cmd[++i] != '"')
				;
		}
		if (cmd[i] == '|' || cmd[i] == '>' || cmd[i] == '<')
		{
			if ((cmd[i] == '<' || cmd[i] == '>' || cmd[i] == '|') && (charisalphaorspace(cmd[i + 1]) == 1))
			{
				if (cmd[i] == '|' && i == 0)
					return (NULL);
				else if (cmd[i + 1] != ' ')
					cmd = add_space(cmd, i);
				else if (cmd[i + 1] == ' ' && (charisalpha(cmd[i + 2]) == 1))
					i++;
				else if (cmd[i] != ' ' || (charisalpha(cmd[i + 3]) == 0))
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

	i = 0;
	check_s = 0;
	check_d = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' && check_s == 0)
			check_s++;
		else if (cmd[i] == '\'' && check_s > 0)
			check_s--;
		else if (cmd[i] == '\"' && check_d == 0)
			check_d++;
		else if (cmd[i] == '\"' && check_d > 0)
			check_d--;
		i++;
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
