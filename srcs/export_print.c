/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:01:33 by mcouppe           #+#    #+#             */
/*   Updated: 2022/07/07 20:38:54 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_qt_env(char **strs)
{
	char	**new_strs;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (strs && strs[i])
		i++;
	new_strs = malloc(sizeof(char *) * (i + 1));
	if (!new_strs)
		return (NULL);
	while (strs && strs[j])
	{
		if (ft_strchr(strs[j], '"') == 0)
			new_strs[j] = ft_dup_special(strs[j]);
		j++;
	}
	new_strs[j] = NULL;
	ft_free_tab(strs);
	return (new_strs);
}

void	ft_print_export_env(t_big_struct *big_s)
{
	t_env_lst	*env;
	char		**env_strs;
	int			i;
	int			size;

	i = -1;
	env = big_s->env_lst;
	size = (ft_lstsize_env(env));
	if (big_s->check_unset == 1)
		size--;
	env_strs = malloc(sizeof(char *) * (size + 1));
	if (!env_strs)
		return ;
	while (env != NULL)
	{
		env_strs[++i] = ft_strdup(env->line);
		if (!env_strs[i])
		{
			ft_free_tab(env_strs);
			return ;
		}
		env = env->next;
	}
	env_strs[size] = NULL;
	env_strs = add_qt_env(env_strs);
	sort_n_print_exp(env_strs, big_s);
	ft_free_tab(env_strs);
}

void	ft_swap(char **strs, int i, int j)
{
	char	*tmp;

	tmp = strs[i];
	strs[i] = strs[j];
	strs[j] = tmp;
}

void	sort_n_print_exp(char **strs, t_big_struct *big_s)
{
	int			i;
	int			j;
	int			size;
	t_env_lst	*env;
	int	check;

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
			if (!strs[i] || strs[i] == NULL)
				check = 1;
			if (!strs[j] || strs[j] == NULL)
				check = 1;
			if (check == 0 && ft_strcmp(strs[i], strs[j]) > 0)
				ft_swap(strs, i, j);
		}
	}
	i = -1;
	while (++i < size)
	{
		if (!strs[i] || strs[i] == NULL)
			;
		else
		{
			ft_putstr_fd("export  ", big_s->cmd_lst->fd_out);
			ft_putendl_fd(strs[i], big_s->cmd_lst->fd_out);
		}
	}
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
	if (check > 0)
	{
		dst[j] = '"';
		dst[++j] = '\0';
	}
	else
		dst[j] = '\0';
	return (dst);
}
