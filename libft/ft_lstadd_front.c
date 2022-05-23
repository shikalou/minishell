/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 16:18:13 by ldinaut           #+#    #+#             */
/*   Updated: 2021/12/01 17:46:38 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	new->next = *alst;
	*alst = new;
}
/*
void    aff_list(t_list *begin)
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

	ft_lstadd_front(&begin, &new);
	aff_list(begin);
	return (0);
}*/
