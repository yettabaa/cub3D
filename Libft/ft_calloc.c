/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:07:02 by yettabaa          #+#    #+#             */
/*   Updated: 2022/11/19 22:07:36 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*blk;

	if (nitems >= SIZE_MAX || size >= SIZE_MAX)
		return (NULL);
	blk = (void *) malloc(nitems * size);
	if (!blk)
		return (NULL);
	ft_bzero(blk, (nitems * size));
	return (blk);
}
