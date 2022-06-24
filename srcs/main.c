/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:00:55 by mcouppe           #+#    #+#             */
/*   Updated: 2022/06/24 18:45:32 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shellmini(t_big_struct *big_struct)
{
	char	*cmd;

	signal(SIGINT, sig_handler);
	while (1)
	{
		cmd = readline("nelson et zor minishell$ ");
		if (!cmd)
			return ;
		add_history(cmd);
		if (ft_parsing(cmd, big_struct))
		{
			ft_exec(big_struct);
			ft_free_between(big_struct);
		}
	}
	free(cmd);
}

int	main(int ac, char **av, char **envp)
{
	t_big_struct	*big_struct;

	(void)ac;
	(void)av;
	big_struct = ft_init_big_struct(envp);
	if (!big_struct)
		return (1);
	shellmini(big_struct);

	printf("\nslt les gars\n");
	ft_free_child(big_struct);
	return (0);
}
