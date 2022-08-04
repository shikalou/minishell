/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:29:38 by ldinaut           #+#    #+#             */
/*   Updated: 2022/08/04 19:38:12 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	havepwd(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], "PWD=", 4) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	addpwd(t_env_lst **env, t_env_lst *pwd)
{
	t_env_lst	*tmp;	

	tmp = *env;
	if (!pwd)
		return ;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = pwd;
}

void	update_spaced_par(char *spaced_par, t_big *b, int i)
{
	char	*tmp;

	b->spaced_par[i] = extended_dollar(spaced_par, b);
	tmp = b->spaced_par[i];
	b->spaced_par[i] = strtrim_aug(tmp, 0);
}
