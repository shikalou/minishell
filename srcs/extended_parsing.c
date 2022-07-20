/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extended_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 13:49:52 by mcouppe           #+#    #+#             */
/*   Updated: 2022/07/20 13:57:45 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_lst(char *cmd, int i, int j, t_big *big_struct)
{
	char		name[100000];
	t_env_lst	*env;
	int			k;

	k = 0;
	env = big_struct->env_lst;
	while (i < j && (cmd[i] && cmd[i] != '='))
	{
		if (cmd[i] && ((ft_isalnum(cmd[i]) == 1) || cmd[i] == '_'))
			name[k++] = cmd[i];
		i++;
	}
	name[k] = '\0';
	while (env)
	{
		if (ft_strncmp(env->line, name, k) == 0 && (env->line)[k] == '=')
			return ((env->line) + (k + 1));
		env = env->next;
	}
	return (NULL);
}

char	*ft_get_env_var(t_big *big_struct, char *cmd, int index)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '"')
		{
			i++;
			while (cmd[i] && cmd[i] != '"')
			{
				if (cmd[i] == '$' && i == index)
					return (expand_first_case(big_struct, i, cmd));
				i++;
			}
			if (cmd[i] && cmd[i] == '"')
				i++;
		}
		else if (cmd[i] == '\'' && ft_memchr_aug(cmd, i, '$') == 1)
			return ("anticonstitution");
		else if (cmd[i] == '$' && i == index)
			return (expand_second_case(big_struct, i, cmd));
		else
			i++;
	}
	return (NULL);
}

int	get_right_size(char *cmd, t_big *big_struct)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd && cmd[i])
	{
		if (cmd[i] == '$')
		{
			count++;
			count += ft_strlen(ft_get_env_var(big_struct, cmd, i));
			if (ft_strlen(ft_get_env_var(big_struct, cmd, i)) == 0)
				count += ft_len_dollar(cmd, i);
			i += ft_len_dollar(cmd, i);
		}
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

char	*extended_dollar(char *cmd, t_big *big_struct)
{
	char	*new_cmd;
	int		i;

	i = 0;
	i = get_right_size(cmd, big_struct);
	new_cmd = malloc(sizeof(char) * i + 1);
	if (!new_cmd)
		return (NULL);
	new_cmd = fill_cmd_expand(cmd, big_struct, new_cmd, 0);
	free(cmd);
	return (new_cmd);
}

void	parsing_quotes(t_big *big_struct)
{
	t_cmd_lst	*head;
	char		*tmp;

	head = big_struct->cmd_lst;
	while (head && head->command)
	{
		if (ft_memchr(head->command, '$', ft_strlen(head->command)))
			head->command = extended_dollar(head->command, big_struct);
		if (head->command && head->command[0] != '\0')
		{
			tmp = head->command;
			head->command = strtrim_aug(tmp);
		}
		head = head->next;
	}
}
