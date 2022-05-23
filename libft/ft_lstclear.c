/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 13:29:58 by ldinaut           #+#    #+#             */
/*   Updated: 2021/12/02 15:56:31 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void	del(void *lst)
{
	42 + 42;
}*/

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*next;

	temp = *lst;
	while (temp)
	{
		next = temp->next;
		ft_lstdelone(temp, del);
		temp = next;
	}
	*lst = NULL;
}

/*void    aff_list(t_list **begin)
{
	t_list	*tmp;
	tmp = *begin;
        while (tmp)
        {
                printf("%p\n", tmp);
                tmp = tmp->next;
        }
}

int	main()
{
	t_list	*list2;
	t_list	*list3;
	t_list	*list4;
	t_list	*list5;
	t_list	**begin;
	void	*new;

	*begin = NULL;
	list2 = ft_lstnew(new);
	list3 = ft_lstnew(new);
	list4 = ft_lstnew(new);
	list5 = ft_lstnew(new);
	list2->next = list3;
	list3->next = list4;
	list4->next = list5;
	*begin = list2;


	aff_list(begin);
	printf("SIZE = %d\n", ft_lstsize(*begin));
	ft_lstclear(begin, del);
	aff_list(begin);
	printf("SIZE = %d\n", ft_lstsize(*begin));
	return (0);
}*/
