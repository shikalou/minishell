/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 12:44:00 by ldinaut           #+#    #+#             */
/*   Updated: 2022/03/15 15:47:36 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin2(char *save, char *ret, char *line)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (save && save[i] != '\0')
	{
		ret[i] = save[i];
		i++;
	}
	if (!line)
	{
		ret[i] = '\0';
		return (ret);
	}
	while (line[++j] != '\0')
	{
		ret[i] = line[j];
		i++;
	}
	ret[i] = '\0';
	free(save);
	return (ret);
}

char	*ft_strjoinn(char *save, char *line)
{
	char	*ret;

	ret = malloc(sizeof(char) * (ft_strlenn(save) + ft_strlenn(line) + 1));
	if (!ret)
	{
		free(save);
		return (NULL);
	}
	ret = ft_strjoin2(save, ret, line);
	return (ret);
}

char	*ft_save_line(int i, char save[BUFFER_SIZE + 1], int fd)
{
	int		index;
	char	*s1;
	char	*line;

	line = NULL;
	while (i > 0)
	{
		index = ft_get_index(save);
		s1 = ft_strdupp(save, index);
		line = ft_strjoinn(line, s1);
		free(s1);
		if (save[index] == '\n')
		{
			ft_update_save(save, index);
			line = ft_strjoinn(line, "\n");
			return (line);
		}
		else
		{
			i = read(fd, save, BUFFER_SIZE);
			save[i] = '\0';
		}
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	save[1024][BUFFER_SIZE + 1];
	int			i;

	if (fd < 0 || BUFFER_SIZE == 0)
		return (NULL);
	i = 1;
	if (save[fd][0] == '\0')
	{
		i = read(fd, save[fd], BUFFER_SIZE);
		save[fd][i] = '\0';
	}
	line = NULL;
	line = ft_save_line(i, save[fd], fd);
	return (line);
}

/*int	main()
{
	int fd = open("text.txt", O_RDONLY);
	int fd2 = open("get_next_line_bonus.h", O_RDONLY);
	char *result;
	char *result2;

	while ((result = get_next_line(fd2)) != NULL)
	{
		printf("%s", result);
		free(result);
		result2 = get_next_line(fd);
		printf("%s", result2);
		free(result2);
	}
	//system("leaks a.out");
	return (0);
}*/
