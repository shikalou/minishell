/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:36:34 by ldinaut           #+#    #+#             */
/*   Updated: 2022/08/04 19:32:13 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_lst	*ft_init_cmd_lst(char **input)
{
	int			i;
	t_cmd_lst	*begin;

	i = 0;
	begin = ft_lstnew_cmd(i, ft_strdup(input[i]));
	while (input[++i])
	{
		ft_lstadd_back_cmd(&begin, ft_lstnew_cmd(i, ft_strdup(input[i])));
	}
	return (begin);
}

t_env_lst	*ft_init_env_lst(char **envp, int i)
{
	t_env_lst	*begin;
	t_env_lst	*safe;
	char		*s;
	char		*s2;

	s = getcwd(NULL, 0);
	safe = NULL;
	if (!havepwd(envp))
	{
		s2 = ft_strjoin("PWD=", s);
		safe = ft_lstnew_env(i, ft_strdup(s2));
		ft_lstadd_back_env(&safe, ft_lstnew_env(i, ft_strdup("SHLVL=0")));
		free(s2);
	}
	if (envp[0] == NULL)
		return (free(s), safe);
	begin = ft_lstnew_env(i, ft_strdup(envp[i]));
	while (envp[++i])
	{
		if (envp[i])
			ft_lstadd_back_env(&begin, ft_lstnew_env(i, ft_strdup(envp[i])));
	}
	addpwd(&begin, safe);
	return (free(s), begin);
}

char	**ft_recover_path(char **envp)
{
	int		i;
	char	*s;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_memcmp(envp[i], "PATH=", 5) == 0)
		{
			s = envp[i] + 5;
			return (ft_split(s, ':'));
		}
		i++;
	}
	return (NULL);
}

char	**ft_new_envp(t_env_lst *env_lst)
{
	int			i;
	int			j;
	char		**envp;
	t_env_lst	*tmp;
	t_env_lst	*tmp2;

	i = 0;
	tmp2 = env_lst;
	j = ft_lstsize_env(tmp2);
	tmp = env_lst;
	envp = malloc(sizeof(char *) * (j + 1));
	if (!envp)
		return (NULL);
	while (tmp && tmp->line)
	{
		envp[i] = ft_strdup(tmp->line);
		tmp = tmp->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

t_big	*ft_init_big(char **envp)
{
	t_big	*big_struct;

	big_struct = malloc(sizeof(t_big));
	if (!big_struct)
		return (NULL);
	big_struct->input = NULL;
	big_struct->absolut_path = NULL;
	big_struct->env_lst = ft_init_env_lst(envp, 0);
	big_struct->envp = ft_new_envp(big_struct->env_lst);
	big_struct->path = ft_recover_path(envp);
	big_struct->cmd_lst = NULL;
	big_struct->cmd_updated = NULL;
	big_struct->spaced_cmd = NULL;
	big_struct->spaced_par = NULL;
	big_struct->status = 0;
	big_struct->c_status = NULL;
	big_struct->random_file = NULL;
	big_struct->check_export = 1;
	big_struct->check_unset = 1;
	big_struct->check_expand_status = 0;
	big_struct->env_size = ft_lstsize_env(big_struct->env_lst);
	ft_update_oldpwd(big_struct, "PWD=", 0);
	return (big_struct);
}
