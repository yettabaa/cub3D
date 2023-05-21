/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:06:13 by yettabaa          #+#    #+#             */
/*   Updated: 2022/11/12 18:54:27 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest == src)
		return (dest);
	i = 0;
	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}

// int main()
// {
// 	int *t[4] = {1,2,5,7};
// 	char str[4] = "yass";
// 	ft_memcpy(t, str, 4);
// 	// ft_memcpy(t+1, str + 1, 1);
// 	// ft_memcpy(t+2, str + 2, 1);
// 	// ft_memcpy(t+3, str + 3, 1);
// 	int i=0;
// 	while(i < 4)
// 	{
// 		printf("%d\n", t[i]);
// 		i++;
// 	}

// }