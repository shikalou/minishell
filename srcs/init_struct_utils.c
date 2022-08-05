/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 19:29:38 by ldinaut           #+#    #+#             */
/*   Updated: 2022/08/05 15:54:05 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	havepwd(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	addpwd(t_env_lst **env, t_env_lst *pwd)
{
	t_env_lst	*tmp;	

	tmp = *env;
	if (!pwd)
		return ;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = pwd;
}

void	update_spaced_par(char *spaced_par, t_big *b, int i)
{
	char	*tmp;

	b->spaced_par[i] = extended_dollar(spaced_par, b);
	tmp = b->spaced_par[i];
	b->spaced_par[i] = strtrim_aug(tmp, 0);
}

char	*ft_strjoin_free2(char const *s1, char *s2)
{
	int			i;
	int			j;
	int			k;
	char		*dest;

	i = 0;
	j = 0;
	if (s2 == NULL || !s2 || s2[j] == '\0')
		return (ft_strdup(s1));
	k = (ft_strlen(s1) + ft_strlen(s2));
	dest = malloc(sizeof(char) * (k + 1));
	if (!dest)
		return (NULL);
	while (s1 && s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
		dest[i++] = s2[j++];
	dest[i] = '\0';
	free(s2);
	return (dest);
}
