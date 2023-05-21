/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 20:20:04 by yettabaa          #+#    #+#             */
/*   Updated: 2022/10/24 01:36:30 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*c;

	if (!del || !lst)
		return ;
	c = *lst;
	while (c)
	{
		if (c->next == NULL)
		{
			ft_lstdelone(*lst, del);
			break ;
		}
		c = c->next;
		ft_lstdelone(*lst, del);
		*lst = c;
	}
	*lst = NULL;
}
