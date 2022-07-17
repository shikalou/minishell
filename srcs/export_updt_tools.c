/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_updt_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:44:37 by mcouppe           #+#    #+#             */
/*   Updated: 2022/07/17 19:34:00 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_remv_plus(char *old)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = malloc(1 * (ft_strlen(old)));
	if (!result)
		return (NULL);
	while (old && old[i])
	{
		if (old[i] && old[i] == '+')
			i++;
		else
			result[j++] = old[i++];
	}
	result[j] = '\0';
	return (result);
}

void	ft_up_env_exp(t_big_struct *big_s, char **var, char **split, int ind)
{
	int		i;

	i = 0;
	while (big_s->envp && big_s->envp[i])
	{
		if (ft_strncmp(big_s->envp[i], var[0], ft_strlen(var[0])) == 0)
		{
			if (var[1] && ft_strchr(var[1], '"') != 0)
				split[ind] = ft_remv_qt_exp(split[ind]);
			free(big_s->envp[i]);
			big_s->envp[i] = ft_strdup(split[ind]);
			return ;
		}
		i++;
	}
}

void	ft_concenv_up(t_big_struct *big_s, char **var, char **split, int ind)
{
	int		i;
	char		*tmp;

	i = 0;
	while (big_s->envp && big_s->envp[i])
	{
		if (ft_strncmp(big_s->envp[i], var[0], ft_strlen(var[0])) == 0)
		{
			if (var[1] && var[1][0] != '\0' &&ft_strchr(var[1], '"') != 0)
			{
				var[1] = ft_remv_qt_exp(var[1]);
				tmp = ft_strjoin(big_s->envp[i], var[1]);
			}
			else
				tmp = ft_remv_plus(split[ind]);
			free(big_s->envp[i]);
			big_s->envp[i] = ft_strdup(tmp);
			free(tmp);
			return ;
		}
		i++;
	}
}

char	**add_qt_env(char **strs)
{
	char	**new_strs;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (strs && strs[++i])
		;
	new_strs = malloc(sizeof(char *) * (i + 1));
	if (!new_strs)
		return (NULL);
	while (j < i)
	{
		if (ft_strchr(strs[j], '"') == 0)
			new_strs[j] = ft_dup_special(strs[j]);
		else
			new_strs[j] = ft_strdup(strs[j]);
		j++;
	}
	new_strs[j] = NULL;
	ft_free_tab(strs);
	return (new_strs);
}

int	exp_update_line(char **var, t_env_lst *env, int i, int j)
{
	int		len_n;
	int		len_v;

	len_n = ft_strlen(var[0]);
	len_v = ft_strlen(var[1]);
	free(env->line);
	env->line = malloc(1 * (len_n + len_v + 2));
	if (!env->line)
		return (1);
	while (++i < len_n)
		env->line[i] = var[0][i];
	env->line[i++] = '=';
	while (++j < len_v)
	{
		env->line[i] = var[1][j];
		i++;
	}
	env->line[i] = '\0';
	return (0);
}
