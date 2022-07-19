/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:35:18 by mcouppe           #+#    #+#             */
/*   Updated: 2022/07/19 20:26:51 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_exp(t_big *big_s, char **var, char **cmd, int ind)
{
	int			len_name;
	int			len_var;
	t_env_lst	*env;

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
			else if (exp_update_line(var, env, -1, -1) == 1)
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

void	ft_change_env_lst(t_big *big_s, char **split_exp)
{
	int			i;
	int			size;
	int			check;
	char		**var;
	t_env_lst	*env;

	i = 0;
	size = 1;
	env = big_s->env_lst;
	while (split_exp && split_exp[size])
		size++;
	while (++i < size)
	{
		check = 0;
		if (parsing_export(split_exp[i]) == 1)
			var = trim_conc_export(split_exp[i]);
		else if (parsing_export(split_exp[i]) == 0)
			var = ft_split_export(split_exp[i], '=');
		else
			check = ft_error_export(big_s, split_exp[i], 0);
		while (env != NULL && check == 0)
		{
			if (ft_strncmp(env->line, var[0], ft_strlen(var[0])) == 0)
			{
				check = updt_e(split_exp, i, big_s, var);
				split_exp[0] = NULL;
			}
			env = env->next;
		}
		if (check == 0)
		{
			ft_new_env_var(big_s, split_exp, i);
			ft_free_tab(var);
		}
		env = big_s->env_lst;
	}
}

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
