/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 14:00:55 by mcouppe           #+#    #+#             */
/*   Updated: 2022/05/25 16:37:32 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	>
	<
		--> [n]>word || [n]<word ([n] can be not specified(it means n == standard output / input))
	|

	>>
		--> [n]>>word (same as above if n not specified) APPEND
	<<
		--> [n]<<[-]word (n can be specified as a specific fd) HEREDOC
*/

/*
	CAS BASIQUES

	check_basique =
	blabla<blabla
	blabla|blabla
	while (s[++i])
	if (s[i] == > || s)
	if s[i]==< ou s[i]==> && s[i+1] && (charisalphaorspace(s[i+1])==1)
		--> if s[i+1] != ' ' && s[i+2]
			s = add_space(s, s[i])
		--> if s[i + 1] == ' ' && charisalpha(s[i+2])
			we cool, we copy, this part is ready to get splitted

	else if (s[i]==< && s[i+1] && s[i + 1]==< && s[i+2] && (charisalphaorspace(s[i+2]) == 1))
		--> << heredoc
	else if (s[i]==> && s[i+1]==> && (charisalphaorspace(s[i+2]) == 1))
		--> >> append
	else
		error syntax
	
	~	~	~	~	~	~	~
	
******* multiples < > >> etc dans la str :
	
	

*/

char	*check_spe_char(char *cmd)
{
	int	i;
	int	len_tmp;

	i = -1;
	len_tmp = ft_strlen(cmd);
/*
	Tant que l'on est dans cmd[i], on itere dedans jusqu'au bout
*/
	while (cmd[++i])
	{
		//Si l'on croise un char | , <  ou > 
		if (cmd[i] == '|' || cmd[i] == '>' || cmd[i] == '<')
		{
			// si ce char est < ou > ou | et que le char suivant est alpha ou espace
			// donc i + 1 n'est pas > ou < ou | mais existe (sinon charisalpha renvoie 0)
			if (cmd[i] == '<' || cmd[i] == '>' || cmd[i] == '|' && (charisalphaorspace(cmd[i + 1]) == 1))
			{
				// check de l'erreur pour la pipe en debut de prompt
				if (cmd[i] == '|' && i == 0)
					return (NULL);
				// si le char d'apres n'est pas espace 
				if (cmd[i + 1] != ' ')
				{
					//on ajoute deux espaces directement a notre str avant(si i > 0) et apres cmd[i]
					cmd = add_space(cmd, i);
				}
				// ensuite verification que ca s'est bien passe ET qu'il y a quelque chose apres ' '
				if (cmd[i + 1] != ' ' || (charisalpha(cmd[i + 2]) == 0))
				{
					// sinon on quit du coup avec return NULL 
					return (NULL);
				}
			}
			// si on est dans le cas du << et qu'il y a bien un char autre que < , > , | juste apres
			else if (cmd[i] == '<' && cmd[i + 1] == '<' && (charisalphaorspace(cmd[i + 2]) == 1))
			{	
				// on ajoute les espaces specifiques au heredoc a cet endroit la de la str
				cmd = add_space_hereapp(cmd, i);
			}
			//si on est dans le cas du >> : meme chose que pour le heredoc
			else if (cmd[i] == '>' && cmd[i + 1] == '>' && (charisalphaorspace(cmd[i + 2]) == 1))
					cmd = add_space_hereapp(cmd, i);
			//else on rentre dans aucune de nos categories == il y a une erreur syntax car un 
			// | ou < ou > est mal utilise, sans rien derriere donc on quit return NULL
			else
				return (NULL);
		}
		// ici, on va checker la len_tmp (la len avant nos changement eventuels de cmd si on add_space)
		// donc SI la len actuelle de cmd est differente de la len de tmp
		if (ft_strlen(cmd) - len_tmp != 0)
		{
			// ALORS on incremente notre i de ce qu'on vient d'ajouter
			// ca nous permet de continuer notre boucle de check meme s'il y a plsrs heredoc etc
			i += ft_strlen(cmd) - len_tmp;
			// du coup on reinit bien cette len_tmp a la new len avec les espaces pour la reutiliser
			len_tmp = ft_strlen(cmd);
		}
		// et hop la boucle continuuuue
	}
	printf("%s\n", cmd);
	// maintenant on devrait avoir une cmd nickel, prete a etre splittee, avec les bons espaces o bons endroits
	return (cmd);
}

int	ft_checkquotes(char *cmd)
{
	int	i;
	int	check_s;
	int	check_d;

	i = 0;
	check_s = 0;
	check_d = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' && check_s == 0)
			check_s++;
		else if (cmd[i] == '\'' && check_s > 0)
			check_s--;
		else if (cmd[i] == '\"' && check_d == 0)
			check_d++;
		else if (cmd[i] == '\"' && check_d > 0)
			check_d--;
		i++;
	}
	return(check_d + check_s);
}


int	ft_parsing(char *cmd)
{
	char **cmd_split;
	int		i;

	i = 0;
	if (ft_checkquotes(cmd) != 0)
	{
		write(2, "Error syntax\n", 13);
		return (0);
	}
	cmd = check_spe_char(cmd);
	// si cmd est NULL (donc s'il y a eu une erreur dans les | ou < ou >), on quit ce prompt et throw error
	if (!cmd)
	{
		write(2, "Error syntax\n", 13);
		return (0);
	}
	cmd_split = ft_split(cmd, ' ');
	while (cmd_split[i])
	{
		ft_printf("%s\n", cmd_split[i]);
		i++;
	}
/*	if (!ft_check_pipe(cmd_split))
	{
		write(2, "Error syntax\n", 13);
		return (0);
	}*/
	return (1);
}

void	shellmini(void)
{
	char *cmd;

	while (1)
	{
		cmd = readline("nelson et zor minishell$ ");
		if (!cmd)
			return ;
		add_history(cmd);
		if(!ft_parsing(cmd))
			continue ;
	}
}

int	main()
{
	shellmini();
	printf("\nslt les gars\n");
	return (0);
}
