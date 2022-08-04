/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cases.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:09:07 by mcouppe           #+#    #+#             */
/*   Updated: 2022/08/02 19:17:00 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cases_testing(t_exp *exp)
{
	if (exp->e == NULL && exp->cmd[exp->i])
		exp->i += ft_len_dollar(exp->cmd, exp->i);
	else if (ft_memcmp(exp->e, exp->token, ft_strlen(exp->token)) == 0)
	{
		exp->up[exp->j++] = exp->cmd[exp->i++];
		while (exp->cmd[exp->i] != '$' && exp->cmd[exp->i] != '\''
			&& exp->cmd[exp->i] != ' ' && exp->cmd[exp->i] != '\0')
			exp->up[exp->j++] = exp->cmd[exp->i++];
	}
	else
	{
		exp->up[exp->j] = '\0';
		exp->sz_up = ft_strlen(exp->up);
		ft_strlcat(exp->up, exp->e, (exp->sz_up + exp->sz_e + 1));
		exp->i += (ft_len_dollar(exp->cmd, exp->i));
		exp->j += exp->sz_e;
	}
}

void	ft_init_expand(t_exp *exp, char *cmd, char *up)
{
	exp->i = 0;
	exp->j = 0;
	exp->cmd = cmd;
	exp->up = up;
	exp->e = NULL;
	exp->sz_e = 0;
	exp->sz_up = 0;
	exp->token = "anticonstitutionnellement";
}

char	*fill_cmd_expand(t_big *big, t_exp *exp)
{
	while (exp->cmd && exp->cmd[exp->i])
	{
		if (exp->cmd[exp->i] == '$')
		{
			exp->e = ft_get_env_var(big, exp->cmd, exp->i);
			exp->sz_e = ft_strlen(exp->e);
			cases_testing(exp);
			if (big->check_expand_status == 1)
				free(exp->e);
		}
		else
			exp->up[exp->j++] = exp->cmd[exp->i++];
	}
	exp->up[exp->j] = '\0';

	return (exp->up);
}

char	*expand_first_case(t_big *big_s, int i, char *cmd)
{
	int		j;

	j = i + 1;
	printf("cmd[%d] = %c\n", i, cmd[i]);
	if (cmd[i + 1] && cmd[i + 1] == '?')
	{
		if (big_s->c_status != NULL)
		{
			free(big_s->c_status);
			big_s->c_status = NULL;
		}
		big_s->c_status = ft_itoa(big_s->status);
		return (expand_status(big_s->c_status, cmd, i, big_s));
	}
	while (cmd[j] && (cmd[j] != ' ' && cmd[j] != '\0' && cmd[j] != '"'
			&& cmd[j] != '$' && cmd[j] != '\''))
		j++;

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
	if (cmd[i + 1] && cmd[i + 1] == '?')
	{
		if (big_s->c_status != NULL)
		{
			free(big_s->c_status);
			big_s->c_status = NULL;
		}
		big_s->c_status = ft_itoa(big_s->status);
		return (expand_status(big_s->c_status, cmd, i, big_s));
	}
	while (cmd[j] && (cmd[j] != ' ' && cmd[j] != '\0' && cmd[j] != '\''
			&& cmd[j] != '"' && cmd[j] != '$'))
		j++;
	if ((j - i) == 1)
		return ("$");
	return (get_env_lst(cmd, i, j, big_s));
}
