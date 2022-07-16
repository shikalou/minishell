/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:01:33 by mcouppe           #+#    #+#             */
/*   Updated: 2022/07/16 19:18:12 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_export_env(t_big_struct *big_s, t_cmd_lst *cmd_lst)
{
	t_env_lst	*env;
	char		**env_strs;
	int			i;
	int			size;

	i = 0;
	env = big_s->env_lst;
	size = (ft_lstsize_env(env));
	env_strs = malloc(sizeof(char *) * (size + 1));
	if (!env_strs)
		return ;
	while (env != NULL)
	{
		env_strs[i] = ft_strdup(env->line);
		if (!env_strs[i])
			return (ft_free_tab(env_strs));
		env = env->next;
		i++;
	}
	env_strs[i] = NULL;
	env_strs = add_qt_env(env_strs);
	sort_n_print_exp(env_strs, big_s, cmd_lst);
	ft_free_tab(env_strs);
}

void	env_print(char **strs, int size, t_cmd_lst *cmd_lst)
{
	int		i;

	i = -1;
	while (++i <= size)
	{
		if (strs[i] && strs[i] != NULL && strs[i][0] != '\0')
		{
			ft_putstr_fd("export  ", cmd_lst->fd_out);
			ft_putendl_fd(strs[i], cmd_lst->fd_out);
		}
	}
}

void	sort_n_print_exp(char **strs, t_big_struct *big_s, t_cmd_lst *cmd_lst)
{
	int			i;
	int			j;
	int			size;
	int			check;
	t_env_lst	*env;

	check = 0;
	i = -1;
	env = big_s->env_lst;
	size = ft_lstsize_env(env);
	while (++i < size)
	{
		j = i;
		while (++j < size)
		{
			check = 0;
			if (!strs[i] || strs[i] == NULL || !strs[j] || strs[j] == NULL)
				check = 1;
			if (check == 0 && ft_strcmp(strs[i], strs[j]) > 0)
				ft_swap_exp(strs, i, j);
		}
	}
	env_print(strs, size, cmd_lst);
}

void	ending_dup_spe(char *dst, int check, int j)
{
	if (check > 0)
	{
		dst[j] = '"';
		dst[++j] = '\0';
	}
	else
		dst[j] = 0;
}

char	*ft_dup_special(char *src)
{
	int		i;
	int		j;
	int		check;
	char	*dst;

	i = 0;
	j = 0;
	check = 0;
	dst = malloc(sizeof(char) * (ft_strlen(src) + 2 + 1));
	if (!dst)
		return (NULL);
	while (src && src[i])
	{
		if ((i >= 1) && src[i] == '=' && check == 0)
		{
			dst[j++] = src[i++];
			dst[j++] = '"';
			check++;
		}
		else
			dst[j++] = src[i++];
	}
	ending_dup_spe(dst, check, j);
	return (dst);
}
