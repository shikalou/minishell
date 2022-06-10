/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtrim_aug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 19:53:29 by mcouppe           #+#    #+#             */
/*   Updated: 2022/06/10 16:52:19 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strtrim_size(char *cmd)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!cmd)
		return (i);
	while (cmd && cmd[i] != '\0')
	{
		if (cmd[i] == '"')
		{
			printf("\n\nCHECK 1 cmd[%d] = %c\n", i, cmd[i]);
			j += 2;
			i++;
			while (cmd[i] && cmd[i] != '"')
				i++;
		}
		else if (cmd[i] == '\'')
		{
			printf("\n\nCHECK 2 cmd[%d] = %c\n", i, cmd[i]);
			j += 2;
			i++;
			while (cmd[i] && cmd[i] != '\'')
				i++;
			printf("-----> cmd[%d] %c\n",i, cmd[i]);
		}
		i++;
		printf("while i = %d\n", i);
	}
	printf("IN TRIM_SIZE %d - %d \n", i , j);
	return (i - j);
}

char	*strtrim_aug(char *cmd)
{
	char	*new_cmd;
	int		i;
	int		j;
	int		size;

	printf("in stritrim cmd = %s\n", cmd);
	size = strtrim_size(cmd);
	i = 0;
	j = 0;
	new_cmd = malloc(sizeof(char) * size + 1);
	if (!new_cmd)
		return (NULL);
	if (size == 0)
		new_cmd = NULL;
	while (cmd && cmd[i])
	{
		if (cmd[i] == '"')
		{
			i++;
			while (cmd[i] && cmd[i] != '"')
				new_cmd[j++] = cmd[i++];
		}
		else if (cmd[i] == '\'')
		{
			i++;
			while (cmd[i] && cmd[i] != '\'')
				new_cmd[j++] = cmd[i++];
		}
		else
		{
			new_cmd[j] = cmd[i];
			j++;
		}
		i++;
	}
	new_cmd[j] = '\0';
//	printf("IN STRTRIM\n\tnew_cmd = %s\tcmd = %s\n", new_cmd, cmd);
	if (cmd)
		free(cmd);
	return (new_cmd);
}
