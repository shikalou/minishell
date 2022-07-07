/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:01:02 by mcouppe           #+#    #+#             */
/*   Updated: 2022/07/07 20:50:16 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*t_env_lst	*ft_recreate_env(int *tmp_tab, char **tmp_strs, char *to_suppr)
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
*//*
void	ft_unset_env(char *to_suppr, t_big_struct *big_s)
{
	t_env_lst	*env;

	env = big_s->env_lst;
	while (env != NULL)
	{
		if (ft_strncmp(env->line, to_suppr, ft_strlen(to_suppr)) == 0)
		{
			printf("test = %s\n", to_suppr);
			ft_lstdelone_env(&env, &free);
		//	env->line = NULL;
			//env->line = env->next->line;
		//	env = env->next;
		}
		env = env->next;
	}
	//big_s->env_lst = env;
	//printf("test = %s\n", big_s->env_lst->next->line);
	env = big_s->env_lst;
	while (env != NULL)
	{
		printf("check \t %s\n", env->line);
		env = env->next;
	}
	free(to_suppr);
}
*/
char	**ft_clear_envp(int ind, char **envp, char *to_suppr)
{
	int		i;
	int		j;
	char		**result;

	i = 0;
	j = 0;
	while (envp && envp[i])
		i++;
//	printf("dans clear envp // i = %d\n", i);
	result = malloc(sizeof(char *) * (i));
	if (!result)
		return (NULL);
	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], to_suppr, ft_strlen(to_suppr)) == 0)
		{
		//	printf("here\n");
//			free(envp[i]);
			i++;
		}
		if (envp[i] && i != ind)
			result[j++] = ft_strdup(envp[i]);
		i++;
	}
	result[j] = NULL;
//	ft_free_tab(envp);
	return (result);
}

void	ft_unset_env(char *to_suppr, t_big_struct *big_s)
{
	//char	**envp;
	char		**split_check;
	int		i;
	int		size;
	t_env_lst	*env_tmp;

	i = 0;
	size = ft_strlen(to_suppr);
	env_tmp = big_s->env_lst;
	while (env_tmp)
	{
		if (ft_strncmp(env_tmp->line, to_suppr, size) == 0)
		{
	//		printf("test 1\n env->line = %s\nto_suppr = %s\n envp[%d] = %s\n", env_tmp->line, to_suppr, i, big_s->envp[i]);
			if (ft_strncmp(big_s->envp[i], to_suppr, size) == 0)
			{
				big_s->envp = ft_clear_envp(i, big_s->envp, to_suppr);
	//			printf("test 2\n envp[%d] after = %s\n et celui avant = %s\n", i, big_s->envp[i], big_s->envp[i - 1]);
				i = -1;
				big_s->check_unset = 1;
				if (ft_strchr(to_suppr, '=') != 0)
				{
					split_check = ft_split_export(to_suppr, '=');
					big_s->check_name = ft_strdup(split_check[1]);
					ft_free_tab(split_check);
				}
			}
			if (i == -1 && ft_strncmp("PATH=", to_suppr, 5) == 0)
			{
				ft_free_tab(big_s->path);
				big_s->path = NULL;
			}
			env_tmp->line = NULL;
		//	free(env_tmp);
			return ;
		}
		env_tmp = env_tmp->next;
		i++;
	}
}

int	ft_unset(t_big_struct *big_s, t_cmd_lst *cmd_lst)
{
	char	**split_unset;
	char	**var;
	char	*dup_line;
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
				dup_line = ft_strdup(env->line);
				ft_unset_env(dup_line, big_s);
				free(dup_line);
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
