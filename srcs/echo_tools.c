/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 15:36:07 by mcouppe           #+#    #+#             */
/*   Updated: 2022/08/03 23:32:42 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_trim_sp(t_big *b)
{
	int		i;
	char	*tmp;

	i = 0;
	while (b->spaced_cmd[i])
	{
		tmp = ft_strdup(b->spaced_cmd[i]);
		free(b->spaced_cmd[i]);
		b->spaced_cmd[i] = ft_strtrim(tmp, " ");
		free(tmp);
		i++;
	}
}

int	echo_check_sp_dq(t_big *b, int i)
{
	int		j;

	j = i + 1;
	while (b->spaced_cmd[i] && b->spaced_cmd[j])
	{
		if ((ft_strcmp(b->spaced_cmd[i], "\"\"") == 0)
			&& (ft_strcmp(b->spaced_cmd[j], "\"\"") == 0))
		{
		//	printf("oui ?\n");
			return (1);
		}
		else if ((ft_strcmp(b->spaced_cmd[i], "''") == 0)
			&& (ft_strcmp(b->spaced_cmd[j], "''") == 0))
			return (1);
		else if (i == 1 && (ft_strcmp(b->spaced_cmd[i], "\"\"") == 0))
		{
		//	printf("coucou\n");
			return (1);
		}
		else
			return (0);
	}
	return (0);
}
