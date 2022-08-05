/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <mcouppe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 21:12:40 by mcouppe           #+#    #+#             */
/*   Updated: 2022/08/05 15:46:27 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_nb_shlvl(char *line, int ind, int i)
{
	int		j;
	int		nbr;
	char	*result;

	j = ind;
	while (line && line[j])
		j++;
	result = malloc(1 * (j - ind) + 1);
	if (!result)
		return (NULL);
	while (line && line[ind])
		result[i++] = line[ind++];
	result[i] = '\0';
	nbr = ft_atoi(result);
	free(result);
	if ((nbr + 1) >= 1000 || (nbr + 1) <= 0)
		return (ft_strdup("1"));
	return (ft_itoa(++nbr));
}

char	*shlvl_line(t_env_lst *env)
{
	int		i;
	char	*to_join;
	char	*name;
	char	*result;

	i = 0;
	while (env->line && env->line[i++])
	{
		if (env->line[i++] == '=')
		{
			to_join = get_nb_shlvl(env->line, i, 0);
			name = ft_strdup("SHLVL=");
			result = ft_strjoin(name, to_join);
			free(name);
			free(to_join);
			free(env->line);
			return (result);
		}
	}
	free(env->line);
	return (NULL);
}

char	**shlvl_envp(t_big *big_s, int ind, int i, int j)
{
	char	*to_join;
	char	**result;

	while (big_s->envp && big_s->envp[i])
		i++;
	result = malloc(sizeof(char *) * (i + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (big_s->envp && big_s->envp[i])
	{
		if (i == ind)
		{
			to_join = get_nb_shlvl(big_s->envp[i], 6, 0);
			result[j++] = ft_strjoin("SHLVL=", to_join);
			free(to_join);
			i++;
		}
		else
			result[j++] = ft_strdup(big_s->envp[i++]);
	}
	ft_free_tab(big_s->envp);
	result[j] = NULL;
	return (result);
}

int	ft_update_shlvl(t_big *big_s)
{
	t_env_lst	*env;
	int			i;

	env = big_s->env_lst;
	i = -1;
	while (env)
	{
		if (ft_strncmp(env->line, "SHLVL", 5) == 0)
			env->line = shlvl_line(env);
		env = env->next;
	}
	while (big_s->envp[++i])
	{
		if (ft_strncmp(big_s->envp[i], "SHLVL", 5) == 0)
			big_s->envp = shlvl_envp(big_s, i, 0, 0);
	}
	return (0);
}
