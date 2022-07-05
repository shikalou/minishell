/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:13:44 by mcouppe           #+#    #+#             */
/*   Updated: 2022/07/05 16:24:14 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_add_char(char *str, char c)
{
	int		i;
	char	*result;

	i = 0;
	result = malloc(1 * (ft_strlen(str) + 2));
	if (!result)
		return (NULL);
	while (str && str[i])
	{
		result[i] = str[i];
		i++;
	}
	result[i] = c;
	result[++i] = '\0';
//	free(str);
	return (result);
}

void	ft_conc_n_add(t_big_struct *big_s, char **var, char **cmd, int ind)
{
	char	*tmp;
	int		len_name;
	t_env_lst	*env;

/*
		a enlever ?
*/
	int		i;
	int		j;
	int		len_var;
	int		len_envvar;

	len_var = ft_strlen(var[1]);
	env = big_s->env_lst;
	len_name = ft_strlen(var[0]);
	while (env != NULL)
	{
		if (ft_memcmp(env->line, var[0], len_name) == 0)
		{
			tmp = ft_add_char(env->line, '=');
			if
		}
	}
}
