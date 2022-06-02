/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:22:19 by ldinaut           #+#    #+#             */
/*   Updated: 2022/06/02 16:52:49 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_big_struct *big_struct)
{
	printf("%s\n", big_struct->absolut_path);
}

void	ft_heredoc(t_big_struct *big_struct)
{
	int		i;
	t_cmd_lst	*head;

	i = 0;
	head = big_struct->cmd_lst;
/*
	j'ai essaye d'isoler chaque heredoc genre 
	si on a << haha << hihi << hoho pouvoir traiter haha hihi et hoho separemment
	pour l'instant c carre genre ca parcours les heredoc progressivement meme si on a des pipes o milieu
	mais y'a peut etre moyen de faire plus opti et aussi ca fait genre 
	pour cmd = <<haha<<hihi<<hoho
	PREMIER : << haha << hihi << hoho
	DEUXIEME : << hihi << hoho
	TROISIEME : << hoho
	et est -ce que ce serait pas mieux de faire 
	PREMIER : << haha
	DEUXIEME : << hihi
	TROISIEME : << hoho
	? jpense ca prend 5 min a faire mais juste comme je suis pas sure que ce soit necessaire 
	pour l'instant, je surcharge pas le code avec ca mais t'embete pas si tu veux qu'on le rajoute je l'adderais stuv
*/

// tant que nos tableau de pipe existent && qu'il y a un heredoc dans ce char * a partir de [i] jusqu'a len
	while (head && ft_strnstr_heredoc(head->command, "<<", ft_strlen(head->command), i))
	{
		// tant qu'il y a un heredoc dans la chaine head->command a partir de l'index [i]
		while (get_next_heredoc(head->command,"<<", i) > 0)
		{
			// print du heredoc cible juste pour voir si c bien cible
			printf("strnstr = %s\n ", ft_strnstr_heredoc(head->command, "<<", ft_strlen(head->command), i));
			// i va s'incrementer  a la prochaine valeur de heredoc,
			// s'il n'y en a pas, on sortira de la boucle de toute facon
			i += (get_next_heredoc(head->command, "<<", i) + 1);
		}
		// on change de char * on passe a la pipe d'apres donc i repart a 0 et head passe au char * d'apres
		i = 0;
		head = head->next;
	}
}

void	ft_exec(t_big_struct *big_struct)
{
	t_cmd_lst *head;

	head = big_struct->cmd_lst;
	// j'ai eu besoin de faire des strnstr exec pour add un split des quotes dans le strnstr
	if (ft_strnstr_exec(head->command, "<<", ft_strlen(head->command)))
		ft_heredoc(big_struct);
	if (ft_strnstr_exec(head->command, "pwd", ft_strlen(head->command)))
		ft_pwd(big_struct);
}
