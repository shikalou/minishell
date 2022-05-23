/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:48:28 by ldinaut           #+#    #+#             */
/*   Updated: 2021/12/02 16:19:34 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/*int	main()
{
	t_list  list1;
        t_list  list2;
        t_list  list3;
        t_list  list4;
        t_list  list5;
        t_list  *begin;

        begin = &list1;
        list1.next = &list2;
        list2.next = &list3;
        list3.next = &list4;
        list4.next = &list5;
        list5.next = 0;

        list1.content = "toto";
        list2.content = "titi";
        list3.content = "tata";
        list4.content = "tete";
        list5.content = "tutu";

	printf("%s\n", ft_lstlast(begin)->content);
	return (0);
}*/
