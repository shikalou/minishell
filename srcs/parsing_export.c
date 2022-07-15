/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <mcouppe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:10:54 by mcouppe           #+#    #+#             */
/*   Updated: 2022/07/15 22:02:53 by mcouppe          ###   ########.fr       */
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

void	ft_conc_update(t_big_struct *big_s, char **var, char **cmd, int ind)
{
	char			*tmp;
	t_env_lst		*env;
	int				len_name;
	int				i;
	int				j;
	int				len_var;
	int				len_envvar;

	len_var = ft_strlen(var[1]);
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
		{
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
			{
				len_envvar = ft_strlen(env->line);
				free(env->line);
				env->line = malloc(1 * (len_envvar + (len_var - 2) + 1));
				if (!env->line)
				{
					free(tmp);
					return ;
				}
				i = 0;
				j = 0;
				while (i < len_envvar)
				{
					env->line[i] = tmp[i];
					i++;
				}
				while (j < (len_var - 1) && var[1][j])
				{
					if (var[1][j] == '"')
						j++;
					else
						env->line[i++] = var[1][j++];
				}
				env->line[i] = '\0';
			}
			free(tmp);
		}
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
	tmp = ft_split_du_futur(var, '=');
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
	while (tmp && tmp[++j])
	{
		if (j == 0)
			result[j] = ft_strtrim(tmp[j], "+");
		else
			result[j] = ft_strdup(tmp[j]);
	}
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
	if (var[i] && var[i] == ' ')
	{
		while (var[i] && var[i] == ' ')
			i++;
	}
	if (var[i] && (ft_isalpha(var[i]) == 0 && var[i] != '_'))
		return (-1);
	i++;
	while (var[i])
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
		i++;
	}
	return (0);
}
