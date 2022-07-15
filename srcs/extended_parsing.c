/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extended_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 13:49:52 by mcouppe           #+#    #+#             */
/*   Updated: 2022/07/15 21:05:17 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_lst(char *cmd, int i, int j, t_big_struct *big_struct)
{
/*
	le (void)big_struct --> je comprends pas du tout pk il est void et du coup 
	comment on a acces a l'env sans passer par big_struct (et du coup a koi sert 
	la fonction et pk elle s'appelle get env lst mdrr jui perdue)
*/
	(void)big_struct;
	char		name[j];
	t_env_lst	*head;
	int			k;

	k = 0;
	head = big_struct->env_lst;
	while (i < j)
	{
		if (cmd[i] && ((ft_isalnum(cmd[i]) == 1) || cmd[i] == '_'))
			name[k++] = cmd[i];
		i++;
	}
	name[k] = '\0';
	while (head)
	{
		if (ft_memcmp(head->line, name, k) == 0 && (head->line)[k] == '=')
			return ((head->line) + (k + 1));
		head = head->next;
	}
	return (NULL);
}

char	*ft_get_env_var(t_big_struct *big_struct, char *cmd, int index)
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
			return ("anticonstitutionnellement");
		else if (cmd[i] == '$' && i == index)
			return (expand_second_case(big_struct, i, cmd));
		else
			i++;
	}
	return (NULL);
}

int	get_right_size(char *cmd, t_big_struct *big_struct)
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

// elle elle va etre dure a reduire lol yoloooo
char	*extended_dollar(char *cmd, t_big_struct *big_struct)
{
	char	*new_cmd;
	char	*env;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	i = get_right_size(cmd, big_struct);
	new_cmd = malloc(sizeof(char) * i + 1);
	if (!new_cmd)
		return (NULL);
	i = 0;
	while (cmd && cmd[i])
	{
		if (cmd[i] == '$')
		{
			env = ft_get_env_var(big_struct, cmd, i);
			len = ft_strlen(env);
			if (env == NULL && cmd[i])
				i += ft_len_dollar(cmd, i);
			else if (ft_memcmp(env, "anticonstitutionnellement", len == 0))
			{
				new_cmd[j++] = cmd[i++];
				while (cmd[i] != '$' && cmd[i] != '\'' && cmd[i] != ' '
					&& cmd[i] != '\0')
					new_cmd[j++] = cmd[i++];
			}
			else
			{
				new_cmd[j] = '\0';
				ft_strlcat(new_cmd, env, (ft_strlen(new_cmd) + len + 1));
				i += (ft_len_dollar(cmd, i));
				j += ft_strlen(env);
			}
		}
		else
		{
			new_cmd[j] = cmd[i];
			i++;
			j++;
		}
	}
	new_cmd[j] = '\0';
	free(cmd);
	return (new_cmd);
}

void	parsing_quotes(t_big_struct *big_struct)
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
