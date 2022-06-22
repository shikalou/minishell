/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retry_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinant <ldinant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:35:18 by mcouppe           #+#    #+#             */
/*   Updated: 2022/06/22 18:17:08 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	add ft_swap libft
*/

void	ft_update_export(t_big_struct *big_s, char **var, char *cmd)
{
	int		i;
	int		j;
	t_env_lst	*env;
	int		len_name;
	int		len_var;

	i = -1;
	j = 0;
	len_name = ft_strlen(var[0]);
	len_var = ft_strlen(var[1]);
	env = big_s->env_lst;
	while (env != NULL)
	{
		if ((ft_memcmp(env->line, var[0], len_name) == 0)
			&& (ft_memcmp(var[0], "PATH", len_name) != 0))
		{
			free(env->line);
			if (ft_strchr(var[1], '"') == 0)
				env->line = ft_strdup(cmd);
			else
			{
				env->line = malloc(1 * len_name + len_var);
				while (++i < len_name)
					env->line[i] = var[0][i];
				env->line[i++] = '=';
				while (++j < (len_var - 1))
				{
					env->line[i] = var[1][j];
					i++;
				}
				env->line[i] = '\0';
			}
		}
		env = env->next;
	}
}

/*void	ft_new_env_var(t_big_struct *big_s, char **split_exp)
{
	t_env_lst	*env;
	t_env_lst	*env_tmp;
	t_env_lst	*new;
	int		i;

	env = big_s->env_lst;
	env_tmp = big_s->env_lst;
	i = 0;
*
	cmp entre env->line[0] genre*
*
	faudrait un lst_new et lst add_back d'un  bail vide au bout de env 
	et la ou on trouve que c l'emplacement de la var exportee on remplace 
	et on remplace ainsi de suite
	avec une var temp
	--> dc il fo un env tmp;
*
	if (ft_strchr(split_exp[1], '"') != 0)
		ft_remv_qt_exp(split_exp[1]);
	new = ft_lstnew_env(i, split_exp[1]);
}*/

void	ft_change_env_lst(t_big_struct *big_s, char **split_exp)
{
//	int		i;
	t_env_lst	*env;
	char		**var;

//	i = 0;
	env = big_s->env_lst;
	var = ft_split(split_exp[2], '=');
	// var [0] == NAME var [1] == value
	while (env != NULL)
	{
		if (ft_memcmp(env->line, var[0], ft_strlen(var[0])) == 0)
		{
			ft_update_export(big_s, var, split_exp[2]);
			return ;
		}
		env = env->next;
	}
	// si on est tjrs la c'est que var[0] n'existait pas dans env_lst
	// donc il faut la creer et l'addback en ordre ascii
//	ft_new_env_var(big_s, split_exp);
}

void	sort_n_print_exp(char **env_strs)
{
	int		i;
	int		j;
	int		size;
//	char		**env_tmp;

	i = 1;
	size = 0;
	while(env_strs && env_strs[size])
		size++;
//	env_tmp = env_strs;
	while (i < size -1)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strncmp(env_strs[i], env_strs[j], ft_strlen(env_strs[i])) > 0)
				ft_swap(env_strs, i, j);
			j++;
		}
		i++;
	}
	i = 0;
	while (env_strs && env_strs[i])
	{
		printf("export  %s\n", env_strs[i]);
		i++;
	}
}

void	ft_print_export_env(t_big_struct *big_s)
{
	t_env_lst	*env;
	t_env_lst	*env_tmp;
	char		**env_strs;
	int		i;

	i = 0;
	env = big_s->env_lst;
	env_tmp = big_s->env_lst;
	env_strs = malloc(sizeof(char *) * ft_lstsize_env(env) + 1);
	if (!env_strs)
		return ;
	while (env_tmp != NULL)
	{
		env_strs[i] = ft_strdup(env->line);
		if (!env_strs[i])
		{
			ft_free_tab(env_strs);
			return ;
		}
		i++;
		env_tmp = env_tmp->next;
	}
	env_strs[i] = NULL;
	sort_n_print_exp(env_strs);
	ft_free_tab(env_strs);
/*
	print en ordre ascii*/
//	env_tmp = env_tmp->next;
	/*while (env != NULL)
	{
		while (env_tmp != NULL && env_tmp[i] >= env[i])
		{
			if (env_tmp[i] == env[i])
				i++;
			if (env_tmp[i] &&  env_tmp[i] <= env[i])
			{
				printf("export  %s\n", env_tmp->line);
				i = 0;
			}
			env_tmp = env_tmp->next;
		}
		env = env->next;
	}*/
/*	while (env != NULL)
	{
		if (env_tmp[i])
		env = env->next;
	}*/
/*	while (env && env != NULL)
	{
		printf("export  %s\n", env->line);
		env = env->next;
	}**/
}

int	ft_export(t_big_struct *big_s, t_cmd_lst *cmd_lst)
{
//	t_env_lst	*env;
	char		**split_export;
	int		i;

/*
	1)	X--> parser la cmd
			[genre de split sur ' ' first apres le 'export' (split[0])puis entre
			 NAME et suite avec le ' = ' +++ apres le '=' 2 solutions : si "
			 split[2] == "tout ce qu'il y a ds quote"
			 else split[2] == toutcequ'ilyaavant ' ' et le reste on ignore.]
			 au fur et a mesure on peut voir :
	2)	X-->est ce qu'il y a des param > 0 = truc + env---> ca c ok
						1 = export var solo
						2 = total
	3)	O-->check split[1] avant le '=' s'il existe deja dans env
			> si oui env_lst = ft_modif(split[1], env_lst)
			> sinon env_lst = ft_lstaddback split[1] +  '=' + split[2]
	4)	-->check des erreurs
*/
//	printf("input[%d] = %s\n", 1, big_s->input[0]);
//	env = big_struct->env_lst;
	i = 0;
	split_export = ft_split_export(cmd_lst->command);
	// ok le split est nickel
	while (split_export && split_export[i])
		i++;
	if (i == 1)
		ft_print_export_env(big_s);
	else if(ft_memcmp(split_export[2], "=", ft_strlen(split_export[2])) == 0)
		ft_change_env_lst(big_s, split_export);
	else
		write(2, "Error syntax\n", 13);
	ft_free_tab(split_export);
	return (1);
}
