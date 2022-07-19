/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 16:56:43 by mcouppe           #+#    #+#             */
/*   Updated: 2022/07/19 18:24:28 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error_export(t_big *big_s, char *split, int check)
{
	if (check == 0)
		ft_putstr_fd("export : `", 2);
	else
		ft_putstr_fd("unset : `", 2);
	ft_putstr_fd(split, 2);
	ft_putendl_fd("':not a valid identifier", 2);
	big_s->status = 1;
	if (check == 0)
		free(split);
	return (1);
}

int	updt_e(char **s, int ind, t_big *big, char **var)
{
	if (parsing_export(s[ind]) == 1)
	{
		ft_concenv_up(big, var);
		ft_conc_update(big, var, s, ind);
	}
	else
	{
		if (ft_strchr(s[ind], '=') != 0)
			ft_up_env_exp(big, var, s, ind);
		update_exp(big, var, s, ind);
	}
	free(s[0]);
	ft_free_tab(var);
	return (1);
}
