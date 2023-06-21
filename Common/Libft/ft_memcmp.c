/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 21:44:08 by yettabaa          #+#    #+#             */
/*   Updated: 2022/10/24 00:46:31 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t	i;

	i = 0;
	if (!n)
		return (0);
	while (i < (n -1) && *(unsigned char *)(str1 + i)
	== *(unsigned char *)(str2 + i))
		i++;
	return (*(unsigned char *)(str1 + i) - *(unsigned char *)(str2 + i));
}
