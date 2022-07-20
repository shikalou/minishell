/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 21:12:40 by mcouppe           #+#    #+#             */
/*   Updated: 2022/07/20 17:57:26 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	here == increment de shlvl
	il faut pouvoir le decrement mais pour le lancer il faut intervenir sur les signaux
	genre si on ctrl D ou exit dans SHLVL > 2 --> alors on shlvl --
	ou alors
	tt simplement lol
	on cree une var ds la big_s en int (+ simple) de shlvl qu'on incremente(quand ft_update_shlvl)
	 et decremente (qd ctrl+D || exit ) et juste moi j'update 
	env et env_lst en fonction de sa valeur
*/

char	*get_nb_shlvl(char *line, int ind)
{
	int		i;
	int		j;
	int		nbr;
	char	*result;

	i = 0;
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
	return (ft_itoa(++nbr));
}

char	*shlvl_line(t_env_lst *env)
{
	int	i;
	char	*to_join;
	char	*name;
	char	*result;

	i = 0;
	while (env->line && env->line[i++])
	{
		if (env->line[i++] == '=')
		{
			to_join = get_nb_shlvl(env->line, i);
			name = ft_strdup("SHLVL=");
			result = ft_strjoin(name, to_join);
			free(name);
			free(to_join);
			free(env->line);
			printf("result final ??? %s\n", result);
			return (result);
		}
	}
	free(env->line);
	return (NULL);
}

char	**shlvl_envp(t_big *big_s, int ind)
{
	int		i;
	int		j;
	char	*name;
	char	*to_join;
	char	**result;

	i = 0;
	j = 0;
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
			to_join = get_nb_shlvl(big_s->envp[i], 6);
			name = ft_strdup("SHLVL=");
			result[j++] = ft_strjoin(name, to_join);
			free(name);
			free(to_join);
			i++;
		}
		else
			result[j++] = ft_strdup(big_s->envp[i++]);
	}
	if (big_s->check_unset > 0 || big_s->check_export > 0)
		ft_free_tab(big_s->envp);
	result[j] = NULL;
	return (result);
}

int	ft_update_shlvl(t_big *big_s)
{
	t_env_lst	*env;
	int		i;

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
			big_s->envp = shlvl_envp(big_s, i);
	}
	big_s->check_export++;
	return (0);
}
