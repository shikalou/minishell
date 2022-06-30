/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <mcouppe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:10:54 by mcouppe           #+#    #+#             */
/*   Updated: 2022/06/30 14:33:27 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	il faut juste ke 1er char soit pas un chiffre
	les autres char peuvent etre chiffres
	all char peuvent etre lettres et '_'
	si quotes --> on les skip juste doubles comme simple


*/
int	parsing_export(char *var)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
}
