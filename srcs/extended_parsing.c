/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extended_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 13:49:52 by mcouppe           #+#    #+#             */
/*   Updated: 2022/06/07 14:55:08 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



char	*strtrim_aug(char *cmd)
{
	char	*new_cmd;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '"')
		{
			j += 2;
			i++;
			while (cmd[i] && cmd[i] != '"')
				i++;
		}
		else if (cmd[i] != '\'')
		{
			j += 2;
			i++;
			while (cmd[i] && cmd[i] != '\'')
				i++;
		}
		i++;
	}
	new_cmd = malloc(sizeof(char) * (i - j) + 1);
	if (!new_cmd)
		return (NULL);
	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] == '"')
		{
			i++;
			while (cmd[i] != '"')
			{
				new_cmd[j] = cmd[i];
				j++;
				i++;
			}
		}
		else if (cmd[i] == '\'')
		{
			i++;
			while(cmd[i] != '\'')
			{
				new_cmd[j] = cmd[i];
				j++;
				i++;
			}
		}
		else
		{
			new_cmd[j] = cmd[i];
			j++;
		}
		i++;
	}
	new_cmd[j] = '\0';
	free(cmd);
	return (new_cmd);
}

void	parsing_quotes(t_big_struct *big_struct)
{
	t_cmd_lst	*head;

	head = big_struct->cmd_lst;
	while (head)
	{
		//regarder si besoin de checker le return NULL malloc
		head->command = strtrim_aug(head->command);
	//	head->command = extended_dollar(head->command);
		head = head->next;
	}
}
