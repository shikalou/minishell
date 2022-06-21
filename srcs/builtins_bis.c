/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:34:55 by mcouppe           #+#    #+#             */
/*   Updated: 2022/06/21 20:30:14 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_export_size(char *cmd, int start)
{
	int 	i;
	int	j;

	i = start;
	j = 0;
	while (cmd && cmd[i])
	{
		if (cmd[i] == '"')
		{
			i++;
			while (cmd && cmd[i] && cmd[i] != '"')
			{
				i++;
				j++;
			}
		}
		else if (cmd[i] == ' ')
			return (j);
		else
			j++;
		i++;
	}
	return (j);
}

int	check_var_in_env(char *cmd, int start, t_env_lst *env_lst)
{
	int		len;
	int		i;

	len = 0;
	i = start;
	while (cmd && cmd[i])
	{
		if(cmd[i] == ' ')
			i++;
		else if (cmd[i] == '=')
			break;
		else
		{
			len++;
			i++;
		}
	}
	printf("len var in checkvarinenv = %d\n", len);
	while (env_lst && env_lst->line)
	{
		if (ft_memcmp(env_lst->line, cmd + start, len) == 0)
			return (1);
		env_lst = env_lst->next;
	}
	return (0);
}

char	*get_export_var(char *cmd, int start, t_big_struct *big_struct)
{
	int		i;
	int		j;
	int		size;
	char	*result;

	i = start;
	j = 0;
	size = get_export_size(cmd, start);
	printf("in get export var size = %d\n", size);
	if (check_var_in_env(cmd, start, big_struct->env_lst) == 1)
		return (NULL);
	result = malloc(sizeof(char) * size + 1);
	if (!result)
		return (NULL);
	while (cmd && cmd[i])
	{
		if (cmd[i] == '"')
		{
			i++;
			while (cmd && cmd[i] && cmd[i] != '"')
				result[j++] = cmd[i++];
		}
		else if (cmd[i] == ' ')
			break;
		else
		{
			result[j] = cmd[i];
			j++;
		}
		i++;
	}
	result[j] = '\0';
	printf("result = %s\n", result);
	return (result);
}

int	ft_export(t_big_struct *big_struct, t_cmd_lst *cmd_lst)
{
	t_env_lst	*head;
	char	*var_exported;
	int		i;
	int		j;

	i = 0;
	j = 6;
	head = big_struct->env_lst;
	while (head)
	{
		i++;
		head = head->next;
	}
	head = big_struct->env_lst;
	while (cmd_lst->command && cmd_lst->command[j] == ' ')
		j++;
	var_exported = get_export_var(cmd_lst->command, j, big_struct);
	if (var_exported != NULL)
		ft_lstadd_back_env(&head, ft_lstnew_env(i, (cmd_lst->command) + j));
	else
		printf("fo update var existante\n");
	head = big_struct->env_lst;
	/*while (head)
	{
		printf("%s\n", head->line);
		head = head->next;
	}*/
//	free(var_exported);
	return (1);
}

int	ft_unset(t_big_struct *big_struct, t_cmd_lst *cmd_lst)
{
	(void)big_struct;
	(void)cmd_lst;
	printf("unset hehehe\n");
	return (1);
}
