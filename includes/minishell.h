/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:47:27 by ldinaut           #+#    #+#             */
/*   Updated: 2022/05/30 16:54:11 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef	struct	s_cmd_lst
{
	int			index;
	char		*command;
	struct s_cmd_lst	*next;
}	t_cmd_lst;

typedef struct	s_global
{
	char	**input;
	char	*absolut_path;
}	t_global;

char	**ft_split_du_futur(char const *s1, char c);

/* parsing */
char	*add_space(char *cmd, int index);
char	*add_space_hereapp(char *cmd, int index);
char	*check_spe_char(char *cmd);

int		charisalphaorspace(char c);
int		charisalpha(char c);
int		ft_parsing(char *cmd, t_global *global);

void	shellmini(t_global *global);

#endif
