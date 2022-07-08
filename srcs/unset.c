/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:01:02 by mcouppe           #+#    #+#             */
/*   Updated: 2022/07/08 14:45:49 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_clear_envp(int ind, char **envp, char *to_suppr, t_big_struct *big_s)
{
	int		i;
	int		j;
	char		**result;

	i = 0;
	j = 0;
	while (envp && envp[i])
		i++;
	result = malloc(sizeof(char *) * (i));
	if (!result)
		return (NULL);
	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], to_suppr, ft_strlen(to_suppr)) == 0)
			i++;
		if (envp[i] && i != ind)
			result[j++] = ft_strdup(envp[i]);
		i++;
		if (envp[i] && (envp[i] == NULL || envp[i][0] == '\0'))
			i++;
	}
	result[j] = NULL;
	if (big_s->check_unset > 0 || big_s->check_export == 1)
		ft_free_tab(envp);
	return (result);
}

void	ft_unset_env(char *to_suppr, t_big_struct *big_s)
{
	char		**split_check;
	int		i;
	int		check;
	int		size;
	t_env_lst	*env_tmp;

	i = 0;
	check = 0;
	size = ft_strlen(to_suppr);
	env_tmp = big_s->env_lst;
	while (env_tmp)
	{
		if (check == 0 && ft_strncmp(env_tmp->line, to_suppr, size) == 0)
		{
			if (big_s->envp[i] && ft_strncmp(big_s->envp[i], to_suppr, size) == 0)
			{
				big_s->envp = ft_clear_envp(i, big_s->envp, to_suppr, big_s);
				i = -1;
				big_s->check_unset++;
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
			free(env_tmp->line);
			check++;
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
