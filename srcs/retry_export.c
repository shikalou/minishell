/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retry_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <mcouppe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 19:35:18 by mcouppe           #+#    #+#             */
/*   Updated: 2022/06/22 12:31:52 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	ft_update_export(t_big_struct *big_s, char **var)
{
	int		i;

	i = 0;
}*/

void	ft_change_env_lst(t_big_struct *big_s, char **split_exp)
{
//	int		i;
	t_env_lst	*env;
	char		**var;

//	i = 0;
	env = big_s->env_lst;
	var = ft_split(split_exp[2], '=');
	// var [0] == NAME var [1] == value
	while (env != NULL)
	{
		if (ft_memcmp(env->line, var[0], ft_strlen(var[0])) == 0)
		{
	//		ft_update_export(big_s, var);
			return ;
		}
		env = env->next;
	}
	// si on est tjrs la c'est que var[0] n'existait pas dans env_lst
	// donc il faut la creer et l'addback en ordre ascii
}

void	ft_print_export_env(t_big_struct *big_s)
{
	t_env_lst	*env;

	env = big_s->env_lst;
	while (env && env != NULL)
	{
		printf("export  %s\n", env->line);
		env = env->next;
	}
}

int	ft_export(t_big_struct *big_s, t_cmd_lst *cmd_lst)
{
//	t_env_lst	*env;
	char		**split_export;
	int		i;

/*
	1)	X--> parser la cmd
			[genre de split sur ' ' first apres le 'export' (split[0])puis entre
			 NAME et suite avec le ' = ' +++ apres le '=' 2 solutions : si "
			 split[2] == "tout ce qu'il y a ds quote" 
			 else split[2] == toutcequ'ilyaavant ' ' et le reste on ignore.]
			 au fur et a mesure on peut voir :
	2)	X-->est ce qu'il y a des param > 0 = truc + env---> ca c ok
						1 = export var solo 
						2 = total
	3)	O-->check split[1] avant le '=' s'il existe deja dans env
			> si oui env_lst = ft_modif(split[1], env_lst)
			> sinon env_lst = ft_lstaddback split[1] +  '=' + split[2]
	4)	-->check des erreurs
*/
//	printf("input[%d] = %s\n", 1, big_s->input[0]);
//	env = big_struct->env_lst;
	i = 0;
	split_export = ft_split_export(cmd_lst->command);
	// ok le split est nickel
	while (split_export && split_export[i])
		i++;
	if (i == 1)
		ft_print_export_env(big_s);
	else if(ft_memcmp(split_export[2], "=", ft_strlen(split_export[2])) == 0)
		ft_change_env_lst(big_s, split_export);
	else
		write(2, "Error syntax\n", 13);
	ft_free_tab(split_export);
	return (1);
}
