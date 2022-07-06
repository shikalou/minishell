/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:01:02 by mcouppe           #+#    #+#             */
/*   Updated: 2022/07/06 17:17:58 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset_env(char *to_suppr, t_big_struct *big_s)
{
	t_env_lst	*env;
	t_env_lst	*tmp;
	int		check;

	check = 0;
	env = big_s->env_lst;
	tmp = big_s->env_lst;
	while (env != NULL && check == 0)
	{
		if (ft_strncmp(env->line, to_suppr, ft_strlen(to_suppr)) == 0)
		{
			free(env->line);
			env = tmp->next;
			while (env != NULL)
				env = env->next;
			check++;	
		}
		else
		{
			tmp = tmp->next;
			env = env->next;
		}
	}
	/*
		print pr check
	*/
}

int	ft_unset(t_big_struct *big_s, t_cmd_lst *cmd_lst)
{
	char	**split_unset;
	char	**var;
	t_env_lst	*env;
	int		i;
	int		check;

	i = 1;
	check = 0;
	env = big_s->env_lst;
	split_unset =  ft_split_du_futur(cmd_lst->command, ' ');
	while (split_unset && split_unset[i])
	{
		var = ft_split_export(split_unset[i], '=');
		while (env != NULL && check == 0)
		{
			if (ft_strncmp(env->line, var[0], ft_strlen(var[0])) == 0)
			{
				ft_unset_env(env->line, big_s);
				check++;
			}	
			env = env->next;
		}
		ft_free_tab(var);
		i++;
	}
	ft_free_tab(split_unset);
	return (1);
}
