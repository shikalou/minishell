/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinant <ldinant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:35:18 by mcouppe           #+#    #+#             */
/*   Updated: 2022/07/08 13:52:14 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_update_export(t_big_struct *big_s, char **var, char **cmd, int ind)
{
	int		i;
	int		j;
	t_env_lst	*env;
	int		len_name;
	int		len_var;

	i = -1;
	j = -1;
	len_name = ft_strlen(var[0]);
	len_var = ft_strlen(var[1]);
	env = big_s->env_lst;
	while (env != NULL)
	{
		if (ft_memcmp(env->line, var[0], len_name) == 0)
		{
			if ((var[1] == NULL
				&& ((int)ft_strlen(env->line)) < (len_name + len_var)))
			{
				free(env->line);
				env->line = ft_strdup(cmd[ind]);
			}
			else if ((var[1] == NULL))
			{
				free(cmd[ind]);
				return ;
			}
			else
			{
				free(env->line);
				env->line = malloc(1 * len_name + len_var + 2);
				if(!env->line)
					return ;
				while (++i < len_name)
					env->line[i] = var[0][i];
				env->line[i++] = '=';
				while (++j < len_var)
				{
					env->line[i] = var[1][j];
					i++;
				}
				env->line[i] = '\0';
			}
		}
		env = env->next;
	}
	free(cmd[ind]);
}

void	ft_new_env_var(t_big_struct *big_s, char **split_exp, int index)
{
	t_env_lst	*env;
	t_env_lst	*new;
	int		i;

	env = big_s->env_lst;
	i = ft_lstsize_env(env);
	if (ft_strchr(split_exp[index], '"') != 0)
		split_exp[index] = ft_remv_qt_exp(split_exp[index]);
	if (ft_eq_check(split_exp[index]) != 0)
		split_exp[index] = ft_remv_eq(split_exp[index]);
	new = ft_lstnew_env(i, split_exp[index]);
//	printf("new->line = %s\n", new->line);
	big_s->envp = ft_addback_tab(big_s, big_s->envp, new->line);
	ft_lstadd_back_env(&env, new);
	big_s->check_export = 1;
}

void	ft_change_env_lst(t_big_struct *big_s, char **split_exp)
{
	int		i;
	int		size;
	int		check;
	t_env_lst	*env;
	char		**var;

	i = 1;
	size = 1;
	env = big_s->env_lst;
	while (split_exp && split_exp[size])
		size++;
	while (i < size)
	{
		check = 0;
		if (parsing_export(split_exp[i]) == 1)
			var = trim_conc_export(split_exp[i]);
		else if (parsing_export(split_exp[i]) == 0)
			var = ft_split_export(split_exp[i], '=');
		else
		{
			ft_putstr_fd("export : `", 2);
			ft_putstr_fd(split_exp[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			big_s->status = 1;
			check++;
			free(split_exp[i]);
		}
		while (env != NULL && check == 0)
		{
			if (ft_strncmp(env->line, var[0], ft_strlen(var[0])) == 0)
			{
				if (parsing_export(split_exp[i]) == 1)
					ft_conc_update(big_s, var, split_exp, i);
				else
					ft_update_export(big_s, var, split_exp, i);
				free(split_exp[0]);
				split_exp[0] = NULL;
				ft_free_tab(var);
				check++;
			}
			env = env->next;
		}
		if (check == 0)
		{
			if (big_s->check_name && ft_strncmp(var[0], big_s->check_name, ft_strlen(var[0])) == 0)
			{
				free(big_s->check_name);
				big_s->check_name = NULL;
				big_s->check_unset--;
			}
			ft_new_env_var(big_s, split_exp, i);
		//	free(split_exp[i]);
			ft_free_tab(var);
		}
		env = big_s->env_lst;
		i++;
	}
}

void	ft_free_tab_special(char **tab, t_big_struct *big_s)
{
	t_env_lst	*env;
	int		i;
	int		size;

	i = 0;
	env = big_s->env_lst;
	size = (ft_lstsize_env(env) - 1);
	if (!tab)
		return;
	while (tab && tab[i] && i < size)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
/*
	problemes de export 
		XOK	export a=lol a+=haha genre sur la meme ligne
		XOK	 export a=lol
		   	export a (a est pas sense etre remplace.....)
		XOK	export a+=123 --> le += ne marche qu'avec les ""
		XOK	 si export a= --> a doit valoir une chaine vide () 
		XOK	 export a+=123 a=po a+="" a=lol
		XOK	le last case ki bug c export a+=123 a=lol
		XOK	y'a bcp de pblm avec split du futur genre des conditionnal jump ou des trucs kom ca
*/

int	ft_export(t_big_struct *big_s, t_cmd_lst *cmd_lst)
{
	char		**split_export;
	int		i;

	i = 0;
	split_export = ft_split_du_futur(cmd_lst->command, ' ');
	while (split_export && split_export[i])
		i++;
	if (i == 1)
		ft_print_export_env(big_s);
	else
		ft_change_env_lst(big_s, split_export);
	free(split_export[0]);
	free(split_export);
	return (1);
}
