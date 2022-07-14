/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bis_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:48:27 by mcouppe           #+#    #+#             */
/*   Updated: 2022/07/14 15:31:28 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_envp(t_big_struct *big_s, char **envp, int ind)
{
	char	**result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (envp && envp[i])
		i++;
	result = malloc(sizeof(char *) * i);
	if (!result)
		return ;
	i = 0;
	while (envp && envp[i])
	{
		if (i == ind)
			i++;
		if (envp[i] && i != ind)
			result[j++] = ft_strdup(envp[i]);
		i++;
		if (envp[i] && (envp[i] == NULL || envp[i][0] == '\0'))
			i++;
	}
	result[j] = NULL;
	if (big_s->check_unset > 0 || big_s->check_export == 1)
		ft_free_tab(big_s->envp);
	big_s->envp = result;
}

void	update_lst(t_big_struct *big_s, char *var)
{
	ft_lstclear_env(big_s->env_lst);
	big_s->env_lst = ft_init_env_lst(big_s->envp);
	big_s->env_size = ft_lstsize_env(big_s->env_lst);
	if (ft_strncmp("PATH", var, 4) == 0)
	{
		ft_free_tab(big_s->path);
		big_s->path = NULL;
	}
}

void	cmp_var(char *var, t_big_struct *big_s)
{
	t_env_lst	*env;
	int		i;
	int		size;

	size = ft_strlen(var);
	i = 0;
	env = big_s->env_lst;
	while (env)
	{
		if ((ft_strncmp(env->line, var, size) == 0)
			&& (env->line[size] == '\0' || env->line[size] == '='))
		{
			update_envp(big_s, big_s->envp, i);
			update_lst(big_s, var);
			big_s->check_unset = 1;
			return ;
		}
		i++;
		env = env->next;
	}
}

int	ft_unset(t_big_struct *big_s, t_cmd_lst *cmd_lst)
{
	t_env_lst	*env;
	char	**spaced_cmd;
	int		i;

	i = 0;
	spaced_cmd = big_s->spaced_cmd;
	env = big_s->env_lst;
	while (spaced_cmd && spaced_cmd[i])
	{
		if (i > 0)
			cmp_var(spaced_cmd[i], big_s);
		i++;
	}
	if (i < 1)
		return (1);
	
/*
	il fo prendre len de spaced_cmd[i] et comparer avec lst env en checkant bien que a len+1 on a un '=' ds l'env 
	ensuite bah du coup fo free/remplace ds envp
	puis bah la meme ds env lst lol hehe facile hein 
*/
	(void)cmd_lst;
	(void) env;
	return (1);
}
