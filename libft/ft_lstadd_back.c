/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 18:39:43 by ldinaut           #+#    #+#             */
/*   Updated: 2021/12/01 19:22:35 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*temp;

	temp = *alst;
	if (!(*alst))
		*alst = new;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

/*void    aff_list(t_list *begin)
{
        while (begin)
        {
                printf("%s\n", (char *)begin->content);
                begin = begin->next;
        }
}

int	main()
{
	t_list	*begin;
	t_list	new;
	t_list	list1;
	t_list	list2;
	
	begin = &list1;
	list1.next = &list2;
	list2.next = 0;

	new.content = "new";
	list1.content = "premier";
	list2.content = "deuxieme";

	new.next = 0;
	ft_lstadd_back(&begin, &new);
	aff_list(begin);

	return (0);
}*/
