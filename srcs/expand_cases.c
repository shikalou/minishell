/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cases.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:09:07 by mcouppe           #+#    #+#             */
/*   Updated: 2022/07/20 13:51:25 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fill_cmd_expand(char *cmd, t_big *big_struct, char *up, int j)
{
	int		i;
	char	*e;

	i = 0;
	while (cmd && cmd[i])
	{
		if (cmd[i] == '$')
		{
			e = ft_get_env_var(big_struct, cmd, i);
			if (e == NULL && cmd[i])
				i += ft_len_dollar(cmd, i);
			else if (ft_memcmp(e, "anticonstitution", ft_strlen(e)) == 0)
			{
				up[j++] = cmd[i++];
				while (cmd[i] != '$' && cmd[i] != '\'' && cmd[i] != ' '
					&& cmd[i] != '\0')
					up[j++] = cmd[i++];
			}
			else
			{
				up[j] = '\0';
				ft_strlcat(up, e, (ft_strlen(up) + ft_strlen(e) + 1));
				i += (ft_len_dollar(cmd, i));
				j += ft_strlen(e);
			}
		}
		else
			up[j++] = cmd[i++];
	}
	up[j] = '\0';
	return (up);
}

char	*expand_first_case(t_big *big_s, int i, char *cmd)
{
	int		j;

	j = i + 1;
	while (cmd[j] && (cmd[j] != ' ' && cmd[j] != '\0' && cmd[j] != '"'
			&& cmd[j] != '$' && cmd[j] != '\''))
		j++;
	if (cmd[i + 1] && cmd[i + 1] == '?' && ((j - i) == 2))
	{
		if (big_s->c_status != NULL)
		{
			free(big_s->c_status);
			big_s->c_status = NULL;
		}
		big_s->c_status = ft_itoa(big_s->status);
		return (big_s->c_status);
	}
	if ((j - i) == 1)
		return ("$");
	return (get_env_lst(cmd, (i + 1), j, big_s));
}

char	*expand_second_case(t_big *big_s, int i, char *cmd)
{
	int		j;

	j = i;
	if (cmd[j] && (cmd[j] != ' ' && cmd[j] != '\0' && cmd[j] != '"'))
		j++;
	while (cmd[j] && (cmd[j] != ' ' && cmd[j] != '\0' && cmd[j] != '\''
			&& cmd[j] != '"' && cmd[j] != '$'))
		j++;
	if (cmd[i + 1] && cmd[i + 1] == '?' && ((j - i) == 2))
	{
		if (big_s->c_status != NULL)
		{
			free(big_s->c_status);
			big_s->c_status = NULL;
		}
		big_s->c_status = ft_itoa(big_s->status);
		return (big_s->c_status);
	}
	if ((j - i) == 1)
		return ("$");
	return (get_env_lst(cmd, i, j, big_s));
}
