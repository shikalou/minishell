/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 12:46:00 by ldinaut           #+#    #+#             */
/*   Updated: 2022/03/15 15:45:13 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_update_save(char *save, int index)
{
	int	i;

	i = 0;
	index++;
	while (save[index])
	{
		save[i] = save[index];
		index++;
		i++;
	}
	while (save[i])
	{
		save[i] = '\0';
		i++;
	}
}

char	*ft_strdupp(const char *s1, int index)
{
	int			i;
	char		*dest;

	i = 0;
	dest = malloc(sizeof(char) * (index + 1));
	if (!dest)
		return (NULL);
	while (i < index)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_get_index(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

size_t	ft_strlenn(char *str)
{
	char	*t;

	t = str;
	if (!str)
		return (0);
	while (*str)
		str++;
	return (str - t);
}
