/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <mcouppe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:10:54 by mcouppe           #+#    #+#             */
/*   Updated: 2022/06/30 16:11:43 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	il faut juste ke 1er char soit pas un chiffre
	les autres char peuvent etre chiffres
	all char peuvent etre lettres et '_'
	si quotes --> on les skip juste doubles comme simple


*/

void	ft_conc_update(t_big_struct *big_s, char **var, char **cmd)
{
//	int		i;
//	int		j;
	char	*tmp;
	int		len_name;
//	int		len_var;
	t_env_lst	*env;

	/*
		en gros update export sof ke la o lieu d'erase avec le strdup juste on strjoin hihi 
		fo verif les free
	*/
//	i = -1;
//	j = 0;
	len_name = ft_strlen(var[0]);
//	len_var = ft_strlen(var[1]);
	env = big_s->env_lst;
	while (env != NULL)
	{
		if ((ft_memcmp(env->line, var[0], len_name) == 0)
			&& (ft_memcmp(var[0], "PATH", len_name) != 0))
		{
			tmp = ft_strdup(env->line);
			free(env->line);
			env->line = ft_strjoin(tmp, var[1]);
			free(tmp);
		}
		env = env->next;
	}
	free(cmd[1]);
}

char	**trim_conc_export(char *var)
{
	char		**tmp;
	char		**result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = ft_split_du_futur(var, '=');
	if (!tmp || tmp == NULL)
		return (NULL);
	while (tmp && tmp[i])
		i++;
	result = malloc(sizeof(char *) * (i + 1));
	if (!result)
	{
		ft_free_tab(tmp);
		return (NULL);
	}
	while (tmp && tmp[j])
	{
		if (j == 0)
			result[j] = ft_strtrim(tmp[j], "+");
		else
			result[j] = ft_strdup(tmp[j]);
		j++;
	}
	result[j] = NULL;
	ft_free_tab(tmp);
	return (result);
}

int	parsing_export(char *var)
{
	int		i;

	i = 0;
	if (!var)
		return (-1);
	if (var[i] && var[i] == ' ')
	{
		while (var[i] && var[i] == ' ')
			i++;
	}
	if (var[i] && (ft_isalpha(var[i]) == 0 && var[i] != '_' && var[i] != '+'))
		return (-1);
	i++;
	while (var[i])
	{
		if (var[i] == '=')
				return (0);
		else if (var[i] == '+')
		{
			if (var[i + 1] && var[i + 1] == '=')
				return (1);
			else
				return (-1);
		}
		else if(var[i] != '_' && (ft_isalnum(var[i]) == 0))
			return (-1);
		i++;
	}
	return (0);
}
