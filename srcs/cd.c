/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:08:11 by ldinaut           #+#    #+#             */
/*   Updated: 2022/06/22 17:14:19 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}

char	*ft_get_home(t_big_struct *big_struct, char *env)
{
	t_env_lst *env_lst;

	env_lst = big_struct->env_lst;
	while (env_lst)
	{
		if (ft_memcmp(env_lst->line, env, ft_strlen(env)) == 0)
			return(env_lst->line + 5);
		env_lst = env_lst->next;
	}
	return (NULL);
}

void	ft_update_oldpwd(t_big_struct *big_struct)
{
	t_env_lst	*env_lst;
	char		*str;

	env_lst = big_struct->env_lst;
	while (env_lst)
	{
		if (ft_memcmp(env_lst->line, "OLDPWD=", 7) == 0)
		{
			str = getcwd(NULL, 0);
			env_lst->line = ft_strjoin("OLDPWD=", str);
			return ;
		}
		env_lst = env_lst->next;
	}
}

void	ft_cd(t_big_struct *big_struct, t_cmd_lst *cmd_lst)
{
	int		i;
	int		ret;
	int		len;
	char	*home;

	i = 1;
	(void)cmd_lst;
	len = ft_count_tab(big_struct->spaced_cmd);
	if (len > 2)
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return ;
	}
	if (len == 1)
	{
		ft_update_oldpwd(big_struct);
		home = ft_get_home(big_struct, "HOME=");
		ret = chdir(home);
		if (ret != 0)
			perror("chdir");
		return ;
	}
	ft_update_oldpwd(big_struct);
	ret = chdir(big_struct->spaced_cmd[i]);
	if (ret != 0)
		perror("chdir");
	return ;
}