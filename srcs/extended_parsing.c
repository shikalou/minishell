/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extended_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 13:49:52 by mcouppe           #+#    #+#             */
/*   Updated: 2022/06/07 18:32:41 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_memchr_aug(char *s, int i, char c)
{
	while (s[i] != '\'')
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}


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

int	ft_len_dollar(char *cmd, int i)
{
//	int	i;
	int	j;

//	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i] == '$')
		{
			while (cmd[i] && cmd[i] != ' ')
			{
				i++;
				j++;
			}
			return (j);
		}
		i++;
	}
	return (j);
}

/*
	le but de cette fonction :

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
//	t_env_lst	*head;
	int		i;
	int		j;

	i = 0;
	j = 0;
	(void)big_struct;
//	head = big_struct->env_lst;
	while (cmd[i])
	{
		if (cmd[i] == '"')
		{
			i++;
			while (cmd[i] != '"')
			{
				if (cmd[i] == '$' && i == index)
				{
					j = i;
					while (cmd[j] != ' ' || cmd[j] != '\0' || cmd[j] != '"')
						j++;
					/*		on interprete
					on prend le  *char de $ jusqu'a ' ' ou '\0'
					on return une fonction qui le cherche dans env_lst
					*/
					printf("coucou\n");
					return(get_env_lst(cmd, i, (j - i)));
				}
				i++;
			}
		}
		else if (cmd[i] == '\'' && ft_memchr_aug(cmd, i, '$') == 1)
		// on interprete pas
		{
			i++;
			while (cmd[i] != '\'')
				i++;
		}
		else if (cmd[i] == '$' && i == index)
			// on interprete
		{
			j = i;
			while (cmd[j] && (cmd[j] != ' ' || cmd[j] != '\0' || cmd[j] != '\'' || cmd[j] != '"'))
				j++;
			printf("et la ?\n");
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
//	int	size;
	int	i;
	int	j;

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
		//		printf("hiihihhii %s\n", env_var);
				new_cmd = ft_strjoin(new_cmd, env_var);
		//		printf("COUCOU JOIN !!!!! %s\n", new_cmd);
				i += ft_len_dollar(cmd, i);
				j += ft_strlen(env_var);
		//		printf("i = %d, j = %d\n", i, j);
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
	//	printf("SALUT LOL C MOI \n");
		head->command = strtrim_aug(head->command);
		head = head->next;
	}
}
