/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extended_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 13:49:52 by mcouppe           #+#    #+#             */
/*   Updated: 2022/06/13 14:36:14 by mcouppe          ###   ########.fr       */
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
//	int		k;
//	char	*ret_void;

	i = 0;
	j = 0;
//	k = 0;
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
					if ((j - i) == 1)
						return("$");
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
		/*	i++;
			while (cmd[i] && cmd[i] != '\'')
			{
				if (cmd[i] == '$' && i == index)
				{
					j = i;
					if (cmd[j] && (cmd[j] != ' ' && cmd[j] != '\0'
							&& cmd[j] != '\''))
						j++;
					while (cmd[j] && (cmd[j] != ' ' && cmd[j] != '\0'
							&& cmd[j] != '\'' && cmd[j] != '$'))
							j++;
					if ((j - i) ==  0)
						i--;
					ret_void = malloc(sizeof(char) * (j - i) + 1);
					if (!ret_void)
						return (NULL);
					j = i;
					if (cmd[j] && (cmd[j] != ' ' && cmd[j] != '\0'
							&& cmd[j] != '\''))
						j++;
					ret_void[k++] = cmd[i];
					while (cmd[j] && (cmd[j] != ' ' && cmd[j] != '\0'
							&& cmd[j] != '\'' && cmd[j] != '$'))
						ret_void[k++] = cmd[j++];
					ret_void[k] = '\0';
					//printf("\n\n\tRET VOID EST EGAL A = %s\n", ret_void);
					return(ret_void);
				}
				i++;
			}
			if (cmd[i] && cmd[i] == '\'')
				i++;*/
			return("anticonstitutionnellement");
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
	//printf("env_var est NULL ????????????????????????????????????????????????\n");
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
			//printf("(if) count = %d, i = %d\n", count, i);
		}
		else
		{
			count++;
			i++;
		//	printf("(else) count = %d, i = %d\n", count, i);
		}
	}
//	printf("get_right_size = %d\n", count);
	return (count);
}

char	*extended_dollar(char *cmd, t_big_struct *big_struct)
{
	char	*new_cmd;
	char	*env_var;
	int		i;
	int		j;

	i = 0;
	j = 0;
/*	if (cmd[i] && cmd[i] == '$')
		i = 1;
	else
	{*/
		// while (cmd[i] && cmd[i] != '$')
		// 	i++;
	//}
	i = get_right_size(cmd, big_struct);
	new_cmd = malloc(sizeof(char) * i + 1);
	if (!new_cmd)
		return (NULL);
	//new_cmd = NULL;
	// if (i == 1 && cmd[i] == '$')
	// 	new_cmd[0] = '\0';
	i = 0;
	while (cmd && cmd[i])
	{
		if (cmd[i] == '$')
		{
			env_var = ft_get_env_var(big_struct, cmd, i);
//			printf("strlen de env_var %ld\n", ft_strlen(env_var));
			if (env_var == NULL && cmd[i])
			{
			//	printf("hihuhuhu\n");
		//		new_cmd[j++] = cmd[i++];
				//ft_strlcat(new_cmd, NULL, 1000);
				i += ft_len_dollar(cmd, i);
			}
			else if(ft_memcmp(env_var, "anticonstitutionnellement", ft_strlen(env_var)) == 0)
			{
				new_cmd[j++] = cmd[i++];
				while (cmd[i] != '$' && cmd[i] != '\'' && cmd[i] != ' ' && cmd[i] != '\0')
					new_cmd[j++] = cmd[i++];
			}
			else
			{
				new_cmd[j] = '\0';
				ft_strlcat(new_cmd, env_var, (ft_strlen(new_cmd) + ft_strlen(env_var) + 1));
				i += (ft_len_dollar(cmd, i));
				j += ft_strlen(env_var);
			}
		}
		else
		{
			//printf("cmd[%d] = %c\n", i, cmd[i]);
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

	head = big_struct->cmd_lst;
	while (head)
	{
		//regarder si besoin de checker le return NULL malloc
		if (ft_memchr(head->command, '$', ft_strlen(head->command)))
			head->command = extended_dollar(head->command, big_struct);
		if (head->command && head->command[0] != '\0')
			head->command = strtrim_aug(head->command);
		head = head->next;
	}
}
