/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:33:54 by mcouppe           #+#    #+#             */
/*   Updated: 2022/07/05 17:20:35 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_eq_check(char *str)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '+' && str[i + 1] && (str[i + 1] == '='))
			return (1);
		i++;
	}
	return (0);
}

char	*ft_remv_eq(char *var)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * (ft_strlen(var) - 1) + 1);
	if (!result)
		return (NULL);
	while (var && var[i])
	{
		if (var[i] == '+' && var[i + 1] && var[i + 1] == '=')
			i++;
		else
			result[j++] = var[i++];
	}
	result[j] = '\0';
	free(var);
	return (result);
}

char	*ft_remv_qt_exp(char *var)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * (ft_strlen(var) - 2) + 1);
	if (!result)
		return (NULL);
	while (var && var[i])
	{
		if (var[i] != '"')
		{
			result[j] = var[i];
			j++;
		}
		i++;
	}
	result[j] = '\0';
	free(var);
	return (result);
}
