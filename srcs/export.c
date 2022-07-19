/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:35:18 by mcouppe           #+#    #+#             */
/*   Updated: 2022/07/19 17:38:48 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_exp(t_big *big_s, char **var, char **cmd, int ind)
{
	int			i;
	int			j;
	int			len_name;
	int			len_var;
	t_env_lst	*env;

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
				return (free(cmd[ind]));
			else if (exp_update_line(var, env, i, j) == 1)
				return ;
		}
		env = env->next;
	}
	free(cmd[ind]);
}

void	ft_new_env_var(t_big *big_s, char **split_exp, int index)
{
	t_env_lst	*env;
	t_env_lst	*new;
	int			i;

	env = big_s->env_lst;
	i = ft_lstsize_env(env);
	if (ft_strchr(split_exp[index], '"') != 0)
		split_exp[index] = ft_remv_qt_exp(split_exp[index]);
	if (ft_eq_check(split_exp[index]) != 0)
		split_exp[index] = ft_remv_eq(split_exp[index]);
	new = ft_lstnew_env(i, split_exp[index]);
	big_s->envp = ft_addback_tab(big_s, big_s->envp, new->line);
	ft_lstadd_back_env(&env, new);
	big_s->check_export = 1;
}

//	NORME TIPS
// puree t'as fait vraiment n'importe koi la y'a rien ki va, assieds toi 5 min
// avant de commencer a mettre les mains ds cette enorme merde
void	ft_change_env_lst(t_big *big_s, char **split_exp)
{
	int			i;
	int			size;
	int			check;
	char		**var;
	t_env_lst	*env;

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
			check = ft_error_export(big_s, split_exp[i]);
		while (env != NULL && check == 0)
		{
			if (ft_strncmp(env->line, var[0], ft_strlen(var[0])) == 0)
			{
				check = updt_e(split_exp, i, big_s, var);
				split_exp[0] = NULL;
			/*	if (parsing_export(split_exp[i]) == 1)
				{
					printf("hihi\n");
					ft_concenv_up(big_s, var);
					ft_conc_update(big_s, var, split_exp, i);
				}
				else
				{
					ft_up_env_exp(big_s, var, split_exp, i);
					ft_update_export(big_s, var, split_exp, i);
				}
				free(split_exp[0]);
				split_exp[0] = NULL;
				ft_free_tab(var);
				check++;*/
			}
			env = env->next;
		}
		if (check == 0)
		{
			if (big_s->check_name
				&& ft_strncmp(var[0], big_s->check_name, ft_strlen(var[0])) == 0)
			{
				free(big_s->check_name);
				big_s->check_name = NULL;
				big_s->check_unset--;
			}
			ft_new_env_var(big_s, split_exp, i);
			ft_free_tab(var);
		}
		env = big_s->env_lst;
		i++;
	}
}

void	ft_free_tab_special(char **tab, t_big *big_s)
{
	t_env_lst	*env;
	int			i;
	int			size;

	i = 0;
	env = big_s->env_lst;
	size = (ft_lstsize_env(env) - 1);
	if (!tab)
		return ;
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
	a= a+=1223 a="haha"
	ca normalement c bon il reste une last dingz avec
	a =  a="haha" a+=123 lol
*/

int	ft_export(t_big *big_s, t_cmd_lst *cmd_lst)
{
	char	**split_export;
	int		i;

	i = 0;
	split_export = ft_sdf(cmd_lst->command, ' ');
	while (split_export && split_export[i])
		i++;
	if (i == 1)
		ft_print_export_env(big_s, cmd_lst);
	else
		ft_change_env_lst(big_s, split_export);
	free(split_export[0]);
	free(split_export);
	return (1);
}
