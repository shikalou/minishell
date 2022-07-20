/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl_decr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:49:18 by mcouppe           #+#    #+#             */
/*   Updated: 2022/07/20 15:30:51 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_nb_shlvl_decr(char *line, int ind)
{
	int		i;
	int		j;
	int		nbr;
	char	*result;

	i = 0;
	j = ind;
	printf("coucou \n");
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
	nbr -= 1;
	printf("nbr est %d\n", nbr);
	return (ft_itoa(nbr));
}

char	*shlvl_line_decr(t_env_lst *env)
{
	int	i;
	char	*to_join;
	char	*name;
	char	*result;

	i = 0;
	printf("hehehe\n");
	while (env->line && env->line[i++])
	{
		if (env->line[i++] == '=')
		{
			to_join = get_nb_shlvl_decr(env->line, i);
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

char	**shlvl_envp_decr(t_big *big_s, int ind)
{
	int		i;
	int		j;
	char	*name;
	char	*to_join;
	char	**result;

	i = 0;
	j = 0;
	printf("hahahaha\n");
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
			printf("\n\nAHSDHSIFHJDGFHNKJ\n\n");
			to_join = get_nb_shlvl_decr(big_s->envp[i], 6);
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

int	ft_update_shlvl_decr(t_big *big_s)
{
	t_env_lst	*env;
	int		i;

	env = big_s->env_lst;
	i = -1;
	printf("mdrrrr\n");
	while (env)
	{
		printf("lalalalalal env_line = %s\n", env->line);
		if (ft_strncmp(env->line, "SHLVL", 5) == 0)
		{
			printf("lol 1\n");
			env->line = shlvl_line_decr(env);
			break ;
		}
		env = env->next;
	}
	while (big_s->envp[++i])
	{
		if (ft_strncmp(big_s->envp[i], "SHLVL", 5) == 0)
		{
			printf("lol 2\n");
			big_s->envp = shlvl_envp_decr(big_s, i);
		}
	}
	big_s->check_export++;
	big_s->shlvl--;
	return (0);
}

