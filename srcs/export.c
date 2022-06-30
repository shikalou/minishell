/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinant <ldinant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:35:18 by mcouppe           #+#    #+#             */
/*   Updated: 2022/06/30 15:23:15 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_update_export(t_big_struct *big_s, char **var, char **cmd)
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
				env->line = ft_strdup(cmd[1]);
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
	free(cmd[1]);
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

void	ft_new_env_var(t_big_struct *big_s, char **split_exp, int index)
{
	t_env_lst	*env;
	t_env_lst	*new;
	int		i;

	env = big_s->env_lst;
	i = ft_lstsize_env(env);
	if (ft_strchr(split_exp[index], '"') != 0)
		split_exp[index] = ft_remv_qt_exp(split_exp[index]);
	new = ft_lstnew_env(i, split_exp[index]);
	ft_lstadd_back_env(&env, new);
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
//		faire un parsing de chaque split_exp[i] ici
		if (parsing_export(split_exp[i]) == 1)
			var = trim_conc_export(split_exp[i]);
	//	si += --> faut deriver sur une autre fonction qui permet de concat
		else if (parsing_export(split_exp[i]) == 0)
			var = ft_split_du_futur(split_exp[i], '=');
		else
		{
			ft_putstr_fd("export : `", 2);
			ft_putstr_fd(split_exp[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			check++;
		}
	// var [0] == NAME var [1] == value
		while (env != NULL && check == 0)
		{
			if (ft_memcmp(env->line, var[0], ft_strlen(var[0])) == 0)
			{
				if (parsing_export(split_exp[i]) == 1)
					ft_conc_update(big_s, var, split_exp)
				else
					ft_update_export(big_s, var, split_exp);
				free(split_exp[0]);
				split_exp[0] = NULL;
				ft_free_tab(var);
				check++;
			}
			env = env->next;
		}
	// si on est tjrs la c'est que var[0] n'existait pas dans env_lst
		if (check == 0)
		{
			ft_new_env_var(big_s, split_exp, i);
			ft_free_tab(var);
		}
		i++;
	}
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

char	*ft_dup_special(char *src)
{
	int		i;
	int		j;
	int		check;
	char	*dst;

	i = 0;
	j = 0;
	check = 0;
	dst = malloc(sizeof(char) * (ft_strlen(src) + 2 + 1));
	if (!dst)
		return (NULL);
	while (src && src[i])
	{
		if ((i > 1) && src[i - 1] == '=' && check == 0)
		{
			dst[j] = '"';
			j++;
			check++;
		}
		dst[j++] = src[i++];
	}
	if(check > 0)
	{
		dst[j] = '"';
		dst[++j] = '\0';
	}
	else
		dst[j] = '\0';
	return (dst);
}

char	**add_qt_env(char **strs)
{
	char	**new_strs;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (strs && strs[i])
		i++;
	new_strs = malloc(sizeof(char *) * (i + 1));
	if (!new_strs)
		return (NULL);
	while (strs && strs[j])
	{
		if (ft_strchr(strs[j], '"') == 0)
			new_strs[j] = ft_dup_special(strs[j]);
		j++;
	}
	new_strs[j] = NULL;
	ft_free_tab(strs);
	return (new_strs);
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
	while (env_tmp->next != NULL)
		env_tmp = env_tmp->next;
	env_strs = malloc(sizeof(char *) * (size + 1));
	if (!env_strs)
		return ;
	while (env != NULL && env->line != NULL)
	{
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
	env_strs = add_qt_env(env_strs);
	sort_n_print_exp(env_strs, big_s);
	ft_free_tab(env_strs);
}

int	ft_export(t_big_struct *big_s, t_cmd_lst *cmd_lst)
{
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
	split_export = ft_split_du_futur(cmd_lst->command, ' ');
	while (split_export && split_export[i])
		i++;
	if (i == 1)
		ft_print_export_env(big_s);
	else /*if(ft_memchr(split_export[1], '=', ft_strlen(split_export[1])) != 0)*/
		ft_change_env_lst(big_s, split_export);
/*	else
		write(2, "Error syntax\n", 13);*/
	
	free(split_export[0]);
	free(split_export);
	return (1);
}
