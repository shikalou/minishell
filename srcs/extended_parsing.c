/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extended_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 13:49:52 by mcouppe           #+#    #+#             */
/*   Updated: 2022/06/07 21:30:38 by mcouppe          ###   ########.fr       */
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

char	*get_env_lst(char *cmd, int i, int j)
{
	(void)cmd;
	(void)i;
	(void)j;
	return ("mcouppe");
}

char	*ft_get_env_var(t_big_struct *big_struct, char *cmd, int index)
{
	int		i;
	int		j;
//	int		k;

	i = 0;
	j = 0;
//	k = 0;
	(void)big_struct;
	while (cmd[i])
	{
		if (cmd[i] == '"')
		{
			i++;
			while (cmd[i] && cmd[i] != '"')
			{
				printf("CHECK 1\tcmd[%d] = %c et index = %d\n", i, cmd[i], index);
				if (cmd[i] == '$' && i == index)
				{
					printf("CHECK 2\tcmd[%d] = %c\n", i, cmd[i]);
					j = i;
					while (cmd[j] && (cmd[j] != ' ' || cmd[j] != '\0'
							|| cmd[j] != '"'))
						j++;
					/*		on interprete
					on prend le  *char de $ jusqu'a ' ' ou '\0'
					on return une fonction qui le cherche dans env_lst
					*/
					return (get_env_lst(cmd, i, (j - i)));
				}
				i++;
			}
			if (cmd[i] && cmd[i] == '"')
				i++;
			printf("CHECK 3\tcmd[%d] = %c\n", i, cmd[i]);
		}
		else if (cmd[i] == '\'' && ft_memchr_aug(cmd, i, '$') == 1)
		// on interprete pas
		{
			i++;
			while (cmd[i] && cmd[i] != '\'')
				i++;
			if (cmd[i] && cmd[i] == '\'')
				i++;
		/*	k = i;
			printf("k first = %d\n i here = %d\n", k, i);
			while (cmd[k] && cmd[k] != '$')
				k++;
			printf("k second = %d\n", k);
			if (cmd[k] == '$')
			{
				index = k;
				printf("donc index = %d\n", index);
			}
			*/	
		}
		else if (cmd[i] == '$' && i == index)
			// on interprete
		{
			j = i;
			while (cmd[j] && (cmd[j] != ' ' || cmd[j] != '\0' || cmd[j] != '\''
					|| cmd[j] != '"'))
				j++;
			return (get_env_lst(cmd, i, (j - i)));
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
	while (cmd[i] && cmd[i] != '$')
		i++;
	new_cmd = malloc(sizeof(char) * i);
	if (!new_cmd)
		return (NULL);
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '$')
		{
			env_var = ft_get_env_var(big_struct, cmd, i);
			if (env_var == NULL && cmd[i])
			{
				while (cmd[i] && (cmd[i] != ' ' || cmd[i] != '\''
						|| cmd[i] != '"'))
					new_cmd[j++] = cmd[i++];
			}
			else
			{
				new_cmd = ft_strjoin(new_cmd, env_var);
				i += ft_len_dollar(cmd, i);
				j += ft_strlen(env_var);
			}
		}
		else
			new_cmd[j++] = cmd[i++];
	}
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
		if (ft_memchr(head->command, '$', ft_strlen(head->command)))
			head->command = extended_dollar(head->command, big_struct);
		head->command = strtrim_aug(head->command);
		head = head->next;
	}
}
