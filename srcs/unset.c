/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:48:27 by mcouppe           #+#    #+#             */
/*   Updated: 2022/07/21 22:22:45 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_envp(t_big *big_s, char **envp, int ind)
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
	i = -1;
	while (envp && envp[++i])
	{
		if (i == ind)
			;
		else if (envp[i] && i != ind)
			result[j++] = ft_strdup(envp[i]);
	}
	result[j] = NULL;
	if (big_s->check_unset > 0 || big_s->check_export == 1)
		ft_free_tab(big_s->envp);
	big_s->envp = result;
}

void	update_lst(t_big *big_s, char *var)
{
	ft_lstclear_env(big_s->env_lst);
	big_s->env_lst = ft_init_env_lst(big_s->envp, 0);
	big_s->env_size = ft_lstsize_env(big_s->env_lst);
	if (ft_strncmp("PATH", var, 4) == 0)
	{
		ft_free_tab(big_s->path);
		big_s->path = NULL;
	}
}

void	cmp_var(char *var, t_big *big_s)
{
	t_env_lst	*env;
	int			i;
	int			size;

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

int	parsing_unset(char *var, t_big *big_s)
{
	int		i;

	i = 0;
	if (!var)
		return (1);
	while (var[i] && var[i] == ' ')
		i++;
	if (var[i] && (ft_isalpha(var[i]) == 0 && var[i] != '_'))
		return (ft_error_export(big_s, var, 1));
	i++;
	while (var[i])
	{
		if (var[i] == '_' || (ft_isalnum(var[i])))
			i++;
		else
			return (ft_error_export(big_s, var, 1));
	}
	return (0);
}

int	ft_unset(t_big *big_s, t_cmd_lst *cmd_lst)
{
	char	**spaced_cmd;
	int		i;

	i = 0;
	spaced_cmd = big_s->spaced_cmd;
	while (spaced_cmd && spaced_cmd[i])
	{
		if (i > 0 && parsing_unset(spaced_cmd[i], big_s) == 0)
			cmp_var(spaced_cmd[i], big_s);
		i++;
	}
	if (i < 1)
		return (1);
	(void)cmd_lst;
	return (1);
}
