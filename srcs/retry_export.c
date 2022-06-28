/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retry_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinant <ldinant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:35:18 by mcouppe           #+#    #+#             */
/*   Updated: 2022/06/28 15:27:32 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		//	free(env->line);
			if (ft_strchr(var[1], '"') == 0)
				env->line = ft_strdup(cmd);
			else
			{
				free(env->line);
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
//	ft_free_tab(var);
}

char	*ft_remv_qt_exp(char *var)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * (ft_strlen(var) - 2) + 1);
	if (!result)
		return (NULL);
	while (var && var[i])
	{
		if (var[i] != '"')
		{
			result[j] = var[i];
			j++;
		}
		i++;
	}
	result[j] = '\0';
	free(var);
	return (result);
}

void	ft_new_env_var(t_big_struct *big_s, char **split_exp)
{
	t_env_lst	*env;
//	t_env_lst	*env_tmp;
	t_env_lst	*new;
	int		i;

	env = big_s->env_lst;
//	env_tmp = big_s->env_lst;
	i = ft_lstsize_env(env);
//	printf("HERE i = %d\n", i);
//	new = ft_lstnew_env(i, split_exp[2]);
/*
	cmp entre env->line[0] genre*
*
	faudrait un lst_new et lst add_back d'un  bail vide au bout de env 
	et la ou on trouve que c l'emplacement de la var exportee on remplace 
	et on remplace ainsi de suite
	avec une var temp
	--> dc il fo un env tmp;
*/
	if (ft_strchr(split_exp[1], '"') != 0)
		split_exp[1] = ft_remv_qt_exp(split_exp[1]);
	new = ft_lstnew_env(i, split_exp[1]);
	printf("new->line = %s\n", split_exp[1]);
	ft_lstadd_back_env(&env, new);
// print de test :
//	env_tmp = big_s->env_lst;
/*	while (env_tmp != NULL)
	{
		printf("%s\n", env_tmp->line);
		env_tmp = env_tmp->next;
	}*/
}

void	ft_change_env_lst(t_big_struct *big_s, char **split_exp)
{
//	int		i;
	t_env_lst	*env;
	char		**var;

//	i = 0;
	env = big_s->env_lst;
	var = ft_split(split_exp[1], '=');
	// var [0] == NAME var [1] == value
	while (env != NULL)
	{
		if (ft_memcmp(env->line, var[0], ft_strlen(var[0])) == 0)
		{
			ft_update_export(big_s, var, split_exp[1]);
			ft_free_tab(var);
			return ;
		}
		env = env->next;
	}
	//printf("test = %s\n", split_exp[1]);
	// si on est tjrs la c'est que var[0] n'existait pas dans env_lst
	ft_new_env_var(big_s, split_exp);
	ft_free_tab(var);
}

void	ft_swap(char **strs, int i, int j)
{
	char	*tmp;

	tmp = strs[i];
	strs[i] = strs[j];
	strs[j] = tmp;
}

void	sort_n_print_exp(char **env_strs, t_big_struct *big_s)
{
	int		i;
	int		j;
	int		size;
	t_env_lst	*env;

	i = 0;
//	size = 0;
//	(void)big_s;
	env = big_s->env_lst;
	size = ft_lstsize_env(env);
/*	while(env_strs && env_strs[size])
		size++;*/
	while (i < size)
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
	while (i < size)
	{
		printf("export  %s\n", env_strs[i]);
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
void	ft_print_export_env(t_big_struct *big_s)
{
	t_env_lst	*env;
	t_env_lst	*env_tmp;
	char		**env_strs;
	int		i;
	int		size;

	i = 0;
	env = big_s->env_lst;
	env_tmp = big_s->env_lst;
	size = (ft_lstsize_env(env));
	printf("FINAL SIZE YES = %d\n", size);
	while (env_tmp->next != NULL)
		env_tmp = env_tmp->next;
	printf("DONC FREROT LE LAST = %s\n", env_tmp->line);
	env_strs = malloc(sizeof(char *) * (size + 1));
	if (!env_strs)
		return ;
	while (env != NULL && env->line != NULL)
	{
	//	printf("env->line = %s\nsize env->line = %ld\n", env->line, ft_strlen(env->line));
		env_strs[i] = ft_strdup(env->line);
		if (!env_strs[i])
		{
			ft_free_tab(env_strs);
			return ;
		}
		i++;
		env = env->next;
	}
	env_strs[size] = NULL;
	sort_n_print_exp(env_strs, big_s);
	ft_free_tab(env_strs);
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
	i = 0;
	split_export = ft_split_export(cmd_lst->command);
	while (split_export && split_export[i])
		i++;
	if (i == 1)
		ft_print_export_env(big_s);
	else if(ft_memchr(split_export[1], '=', ft_strlen(split_export[1])) != 0)
		ft_change_env_lst(big_s, split_export);
	else
		write(2, "Error syntax\n", 13);
//	if (split_export)
//		ft_free_tab(split_export);
//	ft_free_tab(split_export);
//	du coup il faut changer la size OU ajouter un malloc ici ???
	free(split_export[0]);
	free(split_export);
	return (1);
}
