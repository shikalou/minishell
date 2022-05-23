/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:27:01 by ldinaut           #+#    #+#             */
/*   Updated: 2021/12/02 16:37:13 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	int		i;
	int		j;
	t_list	*temp;

	temp = lst;
	j = 0;
	i = ft_lstsize(temp);
	while (j < i)
	{
		f(lst->content);
		j++;
		lst = lst->next;
	}
}
