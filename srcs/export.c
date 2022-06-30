/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinant <ldinant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:35:18 by mcouppe           #+#    #+#             */
/*   Updated: 2022/06/30 18:48:52 by mcouppe          ###   ########.fr       */
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
		if (ft_memcmp(env->line, var[0], len_name) == 0)
		{
			free(env->line);
			if (ft_strchr(var[1], '"') == 0)
				env->line = ft_strdup(cmd[1]);
			else
			{
				env->line = malloc(1 * len_name + len_var);
				if(!env->line)
					return ;
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
		if (parsing_export(split_exp[i]) == 1)
			var = trim_conc_export(split_exp[i]);
		else if (parsing_export(split_exp[i]) == 0)
			var = ft_split_du_futur(split_exp[i], '=');
		else
		{
			ft_putstr_fd("export : `", 2);
			ft_putstr_fd(split_exp[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			check++;
		}
		while (env != NULL && check == 0)
		{
			if (ft_memcmp(env->line, var[0], ft_strlen(var[0])) == 0)
			{
				if (parsing_export(split_exp[i]) == 1)
					ft_conc_update(big_s, var, split_exp);
				else
					ft_update_export(big_s, var, split_exp);
				free(split_exp[0]);
				split_exp[0] = NULL;
				ft_free_tab(var);
				check++;
			}
			env = env->next;
		}
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

	i = -1;
	env = big_s->env_lst;
	size = ft_lstsize_env(env);
	while (++i < size)
	{
		j = i;
		while (++j < size)
		{
			if (ft_strncmp(env_strs[i], env_strs[j], ft_strlen(env_strs[i])) > 0)
				ft_swap(env_strs, i, j);
		}
	}
	i = -1;
	while (++i < size)
	{
		ft_putstr_fd("export  ", big_s->cmd_lst->fd_out);
		ft_putendl_fd(env_strs[i], big_s->cmd_lst->fd_out);
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
	char		**env_strs;
	int		i;
	int		size;

	i = -1;
	env = big_s->env_lst;
	size = (ft_lstsize_env(env));
	env_strs = malloc(sizeof(char *) * (size + 1));
	if (!env_strs)
		return ;
	while (env != NULL && env->line != NULL)
	{
		env_strs[++i] = ft_strdup(env->line);
		if (!env_strs[i])
		{
			ft_free_tab(env_strs);
			return ;
		}
		env = env->next;
	}
	env_strs[size] = NULL;
	env_strs = add_qt_env(env_strs);
	sort_n_print_exp(env_strs, big_s);
	ft_free_tab(env_strs);
}

/*
	problemes de export 
		- export a=lol a+=haha genre sur la meme ligne
		- {export a=lol
		   export a}
		- export a+=123 --> le += ne marche qu'avec les ""
		- si export a= --> a doit valoir une chaine vide () 
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
