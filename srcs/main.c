/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:00:55 by mcouppe           #+#    #+#             */
/*   Updated: 2022/05/30 17:01:50 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_spe_char(char *cmd)
{
	int	i;
	int	len_tmp;

	i = -1;
	len_tmp = ft_strlen(cmd);
	while (cmd[++i])
	{
		if (cmd[i] == '"')
		{
			while (cmd[++i] != '"')
				;
		}
		if (cmd[i] == '|' || cmd[i] == '>' || cmd[i] == '<')
		{
			if ((cmd[i] == '<' || cmd[i] == '>' || cmd[i] == '|') && (charisalphaorspace(cmd[i + 1]) == 1))
			{
				if (cmd[i] == '|' && i == 0)
					return (NULL);
				else if (cmd[i + 1] != ' ')
					cmd = add_space(cmd, i);
				else if (cmd[i + 1] == ' ' && (charisalpha(cmd[i + 2]) == 1))
					i++;
				else if (cmd[i] != ' ' || (charisalpha(cmd[i + 3]) == 0))
					return (NULL);
			}
			else if (cmd[i] == '<' && cmd[i + 1] == '<' && (charisalphaorspace(cmd[i + 2]) == 1))
				cmd = add_space_hereapp(cmd, i);
			else if (cmd[i] == '>' && cmd[i + 1] == '>' && (charisalphaorspace(cmd[i + 2]) == 1))
					cmd = add_space_hereapp(cmd, i);
			else
				return (NULL);
		}
		if (ft_strlen(cmd) - len_tmp != 0)
		{
			i += ft_strlen(cmd) - len_tmp;
			len_tmp = ft_strlen(cmd);
		}
	}
	return (cmd);
}

int	ft_checkquotes(char *cmd)
{
	int	i;
	int	check_s;
	int	check_d;

	i = 0;
	check_s = 0;
	check_d = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' && check_s == 0)
			check_s++;
		else if (cmd[i] == '\'' && check_s > 0)
			check_s--;
		else if (cmd[i] == '\"' && check_d == 0)
			check_d++;
		else if (cmd[i] == '\"' && check_d > 0)
			check_d--;
		i++;
	}
	return(check_d + check_s);
}


int	ft_parsing(char *cmd, t_global *global)
{
	int		i;

	if (ft_checkquotes(cmd) != 0)
	{
		write(2, "Error syntax\n", 13);
		return (0);
	}
	cmd = check_spe_char(cmd);
	if (!cmd)
	{
		write(2, "Error syntax\n", 13);
		return (0);
	}
	global->input = ft_split_du_futur(cmd, '|');
	i = -1;
	printf("avant\n");
	while (global->input[++i] != NULL)
	{
		printf("%s\n", global->input[i]);
	}
	printf("apres\n");
	return (1);
}

void	shellmini(t_global *global)
{
	char *cmd;

	while (1)
	{
		cmd = readline("nelson et zor minishell$ ");
		if (!cmd)
			return ;
		add_history(cmd);
		ft_parsing(cmd, global);
	}
//	free(cmd);
}

int	main()
{
	t_global *global;
	
	global = malloc(sizeof(t_global));
	shellmini(global);
	printf("\nslt les gars\n");
	/*free global*/
	return (0);
}
