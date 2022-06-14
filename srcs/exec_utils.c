/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:02:50 by mcouppe           #+#    #+#             */
/*   Updated: 2022/06/14 13:30:25 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	besoin d'adapter les strnstr aux quotes d'ou ajout du split quotes
	ex = "pwd" ne doit pas s'exec , "pwd" pwd --> doit s'exec
*/
int	get_next_heredoc(char *s1, char *s2, int i)
{
	int		j;
	int		temp;

	if (s2[0] == '\0')
		return (0);
	while (s1[i])
	{
		j = 0;
		if (s1[i] == '"' || s1[i] == '\'')
			i += (ft_split_quotes(s1, i) + 1);
		temp = i;
		while (s1[i] && (s1[i] == s2[j]))
		{
			if (s2[j + 1] == '\0')
				return (i);
			else
			{
				i++;
				j++;
			}
		}
		i = temp;
		i++;
	}
	return (0);
}

char	*ft_strnstr_exec(char *s1, char *s2, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	temp;

	i = 0;
	if ((!s2 || s2[0] == '\0') && s1)
		return (s1);
	while (s1 && s1[i])
	{
		j = 0;
		if (s1[i] == '"' || s1[i] == '\'')
			i += (ft_split_quotes(s1, i) + 1);
		temp = i;
		while (s1[i] && s2[j] && s1[i] == s2[j] && i < n)
		{
			if (!s2[j + 1] || s2[j + 1] == '\0')
				return (&((char *)s1)[temp]);
			i++;
			j++;
		}
		i = temp + 1;
	}
	return (NULL);
}

char	*ft_strnstr_hd(char *s1, char *s2, size_t n, size_t i)
{
	size_t	j;
	size_t	temp;

	if (s2[0] == '\0')
		return ((char *)s1);
	while (s1[i])
	{
		temp = i;
		j = 0;
		while (s1[i] == s2[j] && i < n)
		{
			if (s2[j + 1] == '\0')
				return (&((char *)s1)[temp]);
			else
			{
				i++;
				j++;
			}
		}
		i = temp;
		i++;
	}
	return (NULL);
}

char	*ft_find_check_path(t_big_struct *big_struct, char **spaced_cmd)
{
	int		i;
	char	*temp;

	i = 0;
	/*if (ft_strchr(cmd->arg_path[0], '/'))
		return (ft_check_slash(cmd));
	else
	{*/
		while (big_struct->path[i] != NULL)
		{
			temp = ft_strjoin(big_struct->path[i], "/");
			big_struct->cmd_updated = ft_strjoin(temp, spaced_cmd[0]);
			free(temp);
			printf("\t\t\t\t%s\n", big_struct->cmd_updated);
			if (big_struct->cmd_updated && access(big_struct->cmd_updated, X_OK) == 0)
				return (big_struct->cmd_updated);
			i++;
			free(big_struct->cmd_updated);
		}
		return (NULL);
	//}
}
