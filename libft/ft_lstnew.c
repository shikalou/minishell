/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 12:33:44 by ldinaut           #+#    #+#             */
/*   Updated: 2022/05/31 16:19:04 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *toto)
{
	t_list	*list1;

	list1 = malloc(sizeof(t_list));
	if (!list1)
		return (NULL);
	list1->next = NULL;
	list1->content = toto;
	return (list1);
}

/*int	main()
{
	t_list *str;
	str = ft_lstnew("une dflgdfgdnfhdnghfghkjphrase");
	printf("%s\n", (char *)str->content);
	return (0);
}*/
