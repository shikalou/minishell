/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:36:34 by ldinaut           #+#    #+#             */
/*   Updated: 2022/06/13 16:00:47 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_lst	*ft_init_cmd_lst(char **input)
{
	int			i;
	t_cmd_lst	*begin;

	i = 0;
	begin = ft_lstnew_cmd(i, input[i]);
	while (input[++i])
	{
		ft_lstadd_back_cmd(&begin, ft_lstnew_cmd(i, input[i]));
	}
	return (begin);
}

t_env_lst	*ft_init_env_lst(char **envp)
{
	int			i;
	t_env_lst	*begin;

	i = 0;
	begin = ft_lstnew_env(i, envp[i]);
	while (envp[++i])
		ft_lstadd_back_env(&begin, ft_lstnew_env(i, envp[i]));
	return (begin);
}

t_big_struct	*ft_init_big_struct(char **envp)
{
	t_big_struct	*big_struct;

	big_struct = malloc(sizeof(t_big_struct));
	if (!big_struct)
		return (NULL);
	big_struct->input = NULL;
	big_struct->absolut_path = getcwd(NULL, 0);
	big_struct->env_lst = ft_init_env_lst(envp);
	big_struct->cmd_lst = NULL;
	return (big_struct);
}
