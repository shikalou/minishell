/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:01:02 by mcouppe           #+#    #+#             */
/*   Updated: 2022/07/06 20:24:40 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_lst	*ft_recreate_env(int *tmp_tab, char **tmp_strs, char *to_suppr)
{
	int		size;
	int		i;
	t_env_lst	*env;

	i = 1;
	size = ft_strlen(to_suppr);
	env = ft_lstnew_env(tmp_tab[0], tmp_strs[0]);
	while (tmp_strs[i] != NULL)
	{
		if (ft_strncmp(tmp_strs[i], to_suppr, size) == 0)
			i++;
		if (tmp_strs[i] != NULL)
			ft_lstadd_back_env(&env, ft_lstnew_env(tmp_tab[i], tmp_strs[i]));
		i++;
	}
	return (env);
}

int	*ft_tab_env(t_big_struct *big_s)
{
	int		*tab;
	int		i;
	t_env_lst	*env;

	env = big_s->env_lst;
	i = 0;
	tab = malloc(sizeof(int) * (ft_lstsize_env(env) + 1));
	if (!tab)
		return (0);
	while (env != NULL)
	{
		tab[i] = env->index;
		i++;
		env = env->next;
	}
	tab[i] = 0;
	return (tab);
}

char	**ft_char_tab_env(t_big_struct *big_s)
{
	int		i;
	t_env_lst	*env;
	char	**result;

	env = big_s->env_lst;
	i = 0;
	result = malloc(sizeof(char *) * (ft_lstsize_env(env) + 1));
	if (!result)
		return (NULL);
	while (env != NULL)
	{
		result[i] = ft_strdup(env->line);
		i++;
		env = env->next;
	}
	result[i] = NULL;
	return (result);
}

void	ft_unset_env(char *to_suppr, t_big_struct *big_s)
{
	t_env_lst	*env;
	char	**tmp_strs;
	int		*tmp_tab;
	int		check;

	check = 0;
	printf("\n\nHERE\tHERE\tHERE\n\n");
//	tmp = NULL;
	env = big_s->env_lst;
	tmp_tab = ft_tab_env(big_s);
	tmp_strs = ft_char_tab_env(big_s);
	while (env != NULL && check == 0)
	{
		if (ft_strncmp(env->line, to_suppr, ft_strlen(to_suppr)) == 0)
		{
		//	ft_lstclear_env(big_s->env_lst);
		//	ft_lstclear_env();
			big_s->env_lst = ft_recreate_env(tmp_tab, tmp_strs, to_suppr);
		/*	env = ft_lstnew_env(tmp->index, tmp->line);
			while (tmp)
			{
				if (ft_strncmp(tmp->line, to_suppr, ft_strlen(to_suppr)) == 0)
					tmp = tmp->next;
				if (tmp)
					ft_lstadd_back_env(&env, ft_lstnew_env(tmp->index, tmp->line));
				tmp = tmp->next;
			}*/
			check++;
		}
		else
			env = env->next;
	}
	/*
		print pr check
	*/
/*	env = big_s->env_lst;
	while (env != NULL)
	{
		printf("check \t %s\n", env->line);
		env = env->next;
	}*/
//	free(tmp_tab);
//	ft_free_tab(tmp_strs);
	free(to_suppr);
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
				ft_unset_env(ft_strdup(env->line), big_s);
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
