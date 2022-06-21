/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retry_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <mcouppe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:35:18 by mcouppe           #+#    #+#             */
/*   Updated: 2022/06/22 00:52:03 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_big_struct *big_s, t_cmd_lst *cmd_lst)
{
//	t_env_lst	*env;
	char		**split_export;

/*
	1)	--> parser la cmd
			[genre de split sur ' ' first apres le 'export' (split[0])puis entre
			 NAME et suite avec le ' = ' +++ apres le '=' 2 solutions : si "
			 split[2] == "tout ce qu'il y a ds quote" 
			 else split[2] == toutcequ'ilyaavant ' ' et le reste on ignore.]
			 au fur et a mesure on peut voir :
	2)	-->est ce qu'il y a des param > 0 = truc + env
						1 = export var solo
						2 = total
	3)	-->check split[1] avant le '=' s'il existe deja dans env
			> si oui env_lst = ft_modif(split[1], env_lst)
			> sinon env_lst = ft_lstaddback split[1] +  '=' + split[2]
	4)	-->check des erreurs
*/
//	printf("input[%d] = %s\n", 1, big_s->input[0]);
//	env = big_struct->env_lst;
	(void)big_s;
	split_export = ft_split_export(cmd_lst->command);
	printf("first = %s second = %s\n", split_export[0], split_export[1]);
	// ok le split est nickel
	return (1);
}
