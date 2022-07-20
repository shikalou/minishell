/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:36:34 by ldinaut           #+#    #+#             */
/*   Updated: 2022/07/20 20:34:02 by mcouppe          ###   ########.fr       */
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

t_env_lst	*ft_init_env_lst(char **envp)
{
	int			i;
	t_env_lst	*begin;
	char		*s;
	char		*s2;

	i = 0;
	s = getcwd(NULL, 0);
	if (envp[i] == NULL)
	{
		s2 = ft_strjoin("PWD=", s);
		free(s);
		begin = ft_lstnew_env(i, ft_strdup(s2));
		ft_lstadd_back_env(&begin, ft_lstnew_env(i, ft_strdup("SHLVL=1")));
		free(s2);
		return (begin);
	}
	begin = ft_lstnew_env(i, ft_strdup(envp[i]));
	while (envp[++i])
	{
		if (envp[i])
			ft_lstadd_back_env(&begin, ft_lstnew_env(i, ft_strdup(envp[i])));
		if (envp[i + 1] && (envp[i] == NULL || envp[i][0] == '\0'))
			i++;
	}
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
	big_struct->env_lst = ft_init_env_lst(envp);
	if (envp[0] == NULL)
		big_struct->envp = ft_new_envp(big_struct->env_lst);
	else
		big_struct->envp = envp;
	big_struct->path = ft_recover_path(envp);
	big_struct->cmd_lst = NULL;
	big_struct->cmd_updated = NULL;
	big_struct->spaced_cmd = NULL;
	big_struct->spaced_par = NULL;
	big_struct->status = 0;
	big_struct->c_status = NULL;
	big_struct->random_file = NULL;
	big_struct->check_export = 0;
	big_struct->check_unset = 0;
	big_struct->name_s = 100000;
	big_struct->env_size = ft_lstsize_env(big_struct->env_lst);
	return (big_struct);
}
