/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:00:55 by mcouppe           #+#    #+#             */
/*   Updated: 2022/06/13 16:06:57 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shellmini(t_big_struct *big_struct)
{
	char	*cmd;

	while (1)
	{
		cmd = readline("nelson et zor minishell$ ");
		if (!cmd)
			return ;
		add_history(cmd);
		if (ft_parsing(cmd, big_struct))
		{
			ft_exec(big_struct);
			if (big_struct->cmd_lst)
				ft_lstclear_cmd(big_struct->cmd_lst);
			if (big_struct->input)
				free(big_struct->input);
		}
	}
	free(cmd);
}

int	main(int ac, char **av, char **envp)
{
	t_big_struct	*big_struct;
//	int		i;

	(void)ac;
	(void)av;
//	i = 0;
	big_struct = ft_init_big_struct(envp);
	if (!big_struct)
		return (1);
	shellmini(big_struct);
	printf("\nslt les gars\n");
	ft_lstclear_env(big_struct->env_lst);
//	ft_lstclear_cmd(big_struct->cmd_lst);
	free(big_struct->absolut_path);
/*	while (big_struct->input[i])
		free(big_struct->input[i++]);*/
	//free(big_struct->cmd_lst);
	free(big_struct);
	return (0);
}
