/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:00:55 by mcouppe           #+#    #+#             */
/*   Updated: 2022/07/22 11:46:40 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shellmini(t_big *big_struct)
{
	char	*cmd;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		cmd = readline("nelson et zor minishell$ ");
		if (!cmd)
			return (big_struct->status);
		add_history(cmd);
		if (ft_strlen(cmd) > 0 && ft_parsing(cmd, big_struct))
		{
			ft_exec(big_struct);
			ft_free_between(big_struct);
		}
	}
	free(cmd);
}

int	main(int ac, char **av, char **envp)
{
	t_big	*big_struct;
	int		i;

	(void)av;
	if (ac > 1)
		return (1);
	big_struct = ft_init_big(envp);
	if (!big_struct)
		return (1);
	ft_update_shlvl(big_struct);
	get_value(big_struct, NULL, 0);
	i = shellmini(big_struct);
	printf("\nslt les gars\n");
	ft_free_child(big_struct, 0);
	return (i);
}
