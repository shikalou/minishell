/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_pars_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 12:30:28 by mcouppe           #+#    #+#             */
/*   Updated: 2022/07/19 16:42:55 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_add_char(char *str, char c)
{
	int		i;
	char	*result;

	i = 0;
	result = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!result)
		return (NULL);
	while (str && str[i])
	{
		result[i] = str[i];
		i++;
	}
	result[i] = c;
	result[++i] = '\0';
	return (result);
}

void	ft_cue(t_env_lst *env, char **var, int len_env, char *tmp)
{
	int		i;
	int		j;
	int		len_var;

	len_var = ft_strlen(var[1]);
	i = -1;
	j = -1;
	free(env->line);
	env->line = malloc(1 * (len_env + (len_var + 2) + 1));
	if (!env->line)
	{
		free(tmp);
		return ;
	}
	while (++i < len_env)
		env->line[i] = tmp[i];
	while (++j < (len_var - 1) && var[1][j])
	{
		if (var[1][j] == '"')
			;
		else
			env->line[i++] = var[1][j];
	}
	env->line[i] = '\0';
}

void	ft_conc_main(t_env_lst *env, char **var)
{
	char	*tmp;

	if (ft_strchr(env->line, '=') == 0)
		tmp = ft_add_char(env->line, '=');
	else
		tmp = ft_strdup(env->line);
	if (var[1] && ft_strchr(var[1], '"') == 0)
	{
		free(env->line);
		env->line = ft_strjoin(tmp, var[1]);
	}
	else
		ft_cue(env, var, ft_strlen(env->line), tmp);
	free(tmp);
}
