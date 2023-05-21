/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 01:43:11 by yettabaa          #+#    #+#             */
/*   Updated: 2022/10/24 00:49:31 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newl;
	t_list	*temp;

	if (!f || !del)
		return (NULL);
	newl = NULL;
	while (lst)
	{	
		temp = newl;
		ft_lstadd_back(&newl, ft_lstnew(f(lst->content)));
		if (!newl)
		{
			ft_lstclear(&temp, del);
			break ;
		}
		lst = lst->next;
	}
	return (newl);
}
