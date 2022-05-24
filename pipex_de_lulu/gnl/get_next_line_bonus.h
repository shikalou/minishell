/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 12:45:53 by ldinaut           #+#    #+#             */
/*   Updated: 2022/03/16 19:57:49 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*ft_strdupp(const char *s1, int index);
char	*ft_save_line(int i, char *save, int fd);
char	*ft_strjoinn(char *save, char *line);
char	*ft_strjoin2(char *save, char *ret, char *line);

void	ft_update_save(char *save, int index);

size_t	ft_strlenn(char *str);
int		ft_get_index(char *str);

#endif
