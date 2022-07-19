/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:10:54 by mcouppe           #+#    #+#             */
/*   Updated: 2022/07/19 20:08:07 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_conc_update(t_big *big_s, char **var, char **cmd, int ind)
{
	t_env_lst		*env;
	int				len_name;

	len_name = ft_strlen(var[0]);
	env = big_s->env_lst;
	if (var[1] == NULL)
	{
		free(cmd[ind]);
		return ;
	}
	while (env != NULL)
	{
		if (ft_memcmp(env->line, var[0], len_name) == 0)
			ft_conc_main(env, var);
		env = env->next;
	}
	free(cmd[ind]);
}

char	**trim_conc_export(char *var)
{
	char	**tmp;
	char	**result;
	int		i;
	int		j;

	i = 0;
	j = -1;
	tmp = ft_sdf(var, '=');
	if (!tmp || tmp == NULL)
		return (NULL);
	while (tmp && tmp[i])
		i++;
	result = malloc(sizeof(char *) * (i + 1));
	if (!result)
	{
		ft_free_tab(tmp);
		return (NULL);
	}
	if (tmp && tmp[++j])
		result[j] = ft_strtrim(tmp[j], "+");
	while (tmp && tmp[++j])
			result[j] = ft_strdup(tmp[j]);
	result[j] = NULL;
	ft_free_tab(tmp);
	return (result);
}

int	parsing_export(char *var)
{
	int		i;

	i = 0;
	if (!var)
		return (-1);
	while (var[i] && var[i] == ' ')
			i++;
	if (var[i] && (ft_isalpha(var[i]) == 0 && var[i] != '_'))
		return (-1);
	while (var[++i])
	{
		if (var[i] == '=')
			return (0);
		else if (var[i] == '+')
		{
			if (var[i + 1] && var[i + 1] == '=')
				return (1);
			else
				return (-1);
		}
		else if (var[i] != '_' && (ft_isalnum(var[i]) == 0))
			return (-1);
	}
	return (0);
}
