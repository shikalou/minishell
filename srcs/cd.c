/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:08:11 by ldinaut           #+#    #+#             */
/*   Updated: 2022/07/19 17:47:24 by ldinaut          ###   ########.fr       */
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

char	*ft_get_home(t_big *big_struct, char *env)
{
	t_env_lst	*env_lst;

	env_lst = big_struct->env_lst;
	while (env_lst)
	{
		if (ft_memcmp(env_lst->line, env, ft_strlen(env)) == 0)
			return (env_lst->line + 5);
		env_lst = env_lst->next;
	}
	return (NULL);
}

void	ft_update_oldpwd(t_big *big_struct, char *s)
{
	t_env_lst	*env_lst;
	char		*str;

	env_lst = big_struct->env_lst;
	while (env_lst)
	{
		if (ft_memcmp(env_lst->line, s, (ft_strlen(s))) == 0)
		{
			str = getcwd(NULL, 0);
			free(env_lst->line);
			env_lst->line = ft_strjoin(s, str);
			free(str);
			return ;
		}
		env_lst = env_lst->next;
	}
}

int	ft_cd_len_one(t_big *big_s)
{
	int		ret;
	char	*home;

	home = ft_get_home(big_s, "HOME=");
	if (!home)
	{
		ft_putendl_fd("cd: HOME not set", 2);
		big_s->status = 1;
		return (1);
	}
	ret = chdir(home);
	if (ret != 0)
	{
		perror("chdir");
		return (1);
	}
	ft_update_oldpwd(big_s, "PWD=");
	big_s->status = 0;
	return (1);
}

int	ft_cd(t_big *big_struct)
{
	int		ret;
	int		len;

	len = ft_count_tab(big_struct->spaced_cmd);
	if (len > 2)
	{
		ft_putendl_fd("cd: too many arguments", 2);
		big_struct->status = 1;
		return (1);
	}
	ft_update_oldpwd(big_struct, "OLDPWD=");
	if (len == 1)
		return (ft_cd_len_one(big_struct));
	ret = chdir(big_struct->spaced_cmd[1]);
	if (ret != 0)
	{
		perror("chdir");
		big_struct->status = 1;
		return (1);
	}
	ft_update_oldpwd(big_struct, "PWD=");
	big_struct->status = 0;
	return (1);
}
