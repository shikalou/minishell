/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extended_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 13:49:52 by mcouppe           #+#    #+#             */
/*   Updated: 2022/06/08 16:55:38 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	le but de cette fonction :

	- recuperer une str avec la variable d'environnement ciblee
	- probleme  = si on a plusieurs variable d'environnement
		solution possible = rappeler ft_get_env_var a chaque fois qu'il
				    y a un $ 
				    du coup il faut lui donner en param le i de cmd[i]
				    pour savoir ou on en est dans cmd

				    par contre : pour le malloc general, on peut pas encore le faire
				donc on va le faire petit a petit
*/

char	*get_env_lst(char *cmd, int i, int j, t_big_struct *big_struct)
{
	(void)big_struct;
	char	name[j];
	t_env_lst	*head;
	int		k;

	k = 0;
	head = big_struct->env_lst;
	while(i < j)
	{
		if (cmd[i] && ((ft_isalnum(cmd[i]) == 1) || cmd[i] == '_'))
			name[k++] = cmd[i];
		i++;
	}
	name[k] = '\0';
	while (head)
	{
		if (ft_memcmp(head->line, name, k) == 0 && (head->line)[k] == '=')
			return((head->line)+ (k + 1));
		head = head->next;
	}
	return (NULL);
}

char	*ft_get_env_var(t_big_struct *big_struct, char *cmd, int index)
{
	int		i;
	int		j;
	int		k;
	char	*ret_void;

	i = 0;
	j = 0;
	k = 0;
	while (cmd[i])
	{
		if (cmd[i] == '"')
		{
			i++;
			while (cmd[i] && cmd[i] != '"')
			{
				if (cmd[i] == '$' && i == index)
				{
					j = i;
					if (cmd[j] && (cmd[j] != ' ' && cmd[j] != '\0'
							&& cmd[j] != '"'))
						j++;
					while (cmd[j] && (cmd[j] != ' ' && cmd[j] != '\0'
							&& cmd[j] != '"' && cmd[j] != '$'))
						j++;
					/*		on interprete
					on prend le  *char de $ jusqu'a ' ' ou '\0'
					on return une fonction qui le cherche dans env_lst
					*/
					return (get_env_lst(cmd, (i + 1), j, big_struct));
				}
				i++;
			}
			if (cmd[i] && cmd[i] == '"')
				i++;
		}
		else if (cmd[i] == '\'' && ft_memchr_aug(cmd, i, '$') == 1)
		// on interprete pas
		{
			i++;
			while (cmd[i] && cmd[i] != '\'')
			{
				if (cmd[i] == '$')
				{
					j = i;
					if (cmd[j] && (cmd[j] != ' ' && cmd[j] != '\0'
							&& cmd[j] != '"'))
						j++;
					while (cmd[j] && (cmd[j] != ' ' && cmd[j] != '\0'
							&& cmd[j] != '"' && cmd[j] != '$'))
							j++;
					ret_void = malloc(sizeof(char) * (j - i) + 1);
					if (!ret_void)
						return (NULL);
					j = i;
					if (cmd[j] && (cmd[j] != ' ' && cmd[j] != '\0'
							&& cmd[j] != '"'))
						j++;
					while (cmd[j] && (cmd[j] != ' ' && cmd[j] != '\0'
							&& cmd[j] != '"' && cmd[j] != '$'))
						ret_void[k++] = cmd[j++];
					ret_void[k] = '\0';
					return(ret_void);
				}
				i++;
			}
			if (cmd[i] && cmd[i] == '\'')
				i++;
		}
		else if (cmd[i] == '$' && i == index)
			// on interprete
		{
			j = i;
			if (cmd[j] && (cmd[j] != ' ' && cmd[j] != '\0'
					&& cmd[j] != '"'))
				j++;
			while (cmd[j] && (cmd[j] != ' ' && cmd[j] != '\0' && cmd[j] != '\''
					&& cmd[j] != '"' && cmd[j] != '$'))
				j++;
			return (get_env_lst(cmd, (i), j, big_struct));
		}
		else
			i++;
	}
	return (NULL);
}

char	*extended_dollar(char *cmd, t_big_struct *big_struct)
{
	char	*new_cmd;
	char	*env_var;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (cmd[i] && cmd[i] == '$')
		i = 1;
	else
	{	
		while (cmd[i] && cmd[i] != '$')
			i++;
	}
	new_cmd = malloc(sizeof(char) * i);
	if (!new_cmd)
		return (NULL);
	new_cmd = NULL;
/*	if (i == 1 && cmd[i] == '$')
		new_cmd[0] = '\0';*/
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '$')
		{
			env_var = ft_get_env_var(big_struct, cmd, i);
			if (env_var == NULL && cmd[i])
			{
				new_cmd =  ft_strjoin(new_cmd, NULL);
				i += ft_len_dollar(cmd , i);
		/*		while (cmd[i] && (cmd[i] != ' ' && cmd[i] != '\''
						&& cmd[i] != '"'))
					new_cmd[j++] = cmd[i++];*/
			}
			else
			{
		//		printf("\n\t\tCHECK 3\tenv var = %s\n", env_var);
				new_cmd = ft_strjoin(new_cmd, env_var);
				i += (ft_len_dollar(cmd, i));
				j += ft_strlen(env_var);
		//		printf("\n\t\tCHECK 4\t cmd[%d] = %c\n", i, cmd[i]);
			}
		}
		else
		{
			new_cmd[j++] = cmd[i++];
		}
	}
	free(cmd);
//	printf("\n\n\t\t\tCHECK 5\nnew_cmd = %s\n\n", new_cmd);
	return (new_cmd);
}

void	parsing_quotes(t_big_struct *big_struct)
{
	t_cmd_lst	*head;

	head = big_struct->cmd_lst;
	while (head)
	{
		//regarder si besoin de checker le return NULL malloc
		if (ft_memchr(head->command, '$', ft_strlen(head->command)))
			head->command = extended_dollar(head->command, big_struct);
		head->command = strtrim_aug(head->command);
		head = head->next;
	}
}
