/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extended_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 13:49:52 by mcouppe           #+#    #+#             */
/*   Updated: 2022/08/04 19:34:54 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_lst(char *cmd, int i, int j, t_big *big_struct)
{
	char		name[NAME_S];
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
		{
			if (env->line[k + 1] == '\0')
				return (" ");
			return ((env->line) + (k + 1));
		}
		env = env->next;
	}
	return (NULL);
}

char	*ft_get_env_var(t_big *big_struct, char *cmd, int index)
{
	int	i;

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
			return ("anticonstitutionnellement");
		else if (cmd[i] == '$' && i == index)
			return (expand_second_case(big_struct, i, cmd));
		else
			i++;
	}
	return (NULL);
}

int	get_right_size(char *cmd, t_big *big_struct, int i)
{
	int		count;
	char	*tmp;

	count = 0;
	while (cmd && cmd[i])
	{
		if (cmd[i] == '$')
		{
			count++;
			tmp = ft_get_env_var(big_struct, cmd, i);
			count += ft_strlen(tmp);
			if (ft_strlen(tmp) == 0)
				count += ft_len_dollar(cmd, i);
			i += ft_len_dollar(cmd, i);
			if (big_struct->check_expand_status == 1)
				free(tmp);
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
	t_exp	exp;
	int		i;

	i = 0;
	i = get_right_size(cmd, big_struct, 0);
	new_cmd = malloc(sizeof(char) * i + 1);
	if (!new_cmd)
		return (NULL);
	ft_init_expand(&exp, cmd, new_cmd);
	new_cmd = fill_cmd_expand(big_struct, &exp);
	free(cmd);
	return (new_cmd);
}

void	parsing_quotes(t_big *big_struct)
{
	t_cmd_lst	*head;
	char		*tmp;
	int			i;

	i = 0;
	head = big_struct->cmd_lst;
	while (head && head->command)
	{
		if (ft_memchr(head->command, '$', ft_strlen(head->command)))
		{
			big_struct->check_expand_status = 0;
			head->command = extended_dollar(head->command, big_struct);
		}
		if (head->command && head->command[0] != '\0')
		{
			tmp = head->command;
			head->command = strtrim_aug(tmp, i);
			i++;
		}
		head = head->next;
	}
}
