/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 15:37:52 by yettabaa          #+#    #+#             */
/*   Updated: 2022/10/26 19:12:06 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	size_t	j;

	j = 1;
	if (s1 > s2)
	{
		while (j <= n)
		{
			((char *)s1)[n - j] = ((char *)s2)[n - j];
			j++;
		}
	}
	else
		ft_memcpy(s1, s2, n);
	return (s1);
}
