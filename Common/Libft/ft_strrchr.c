/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 22:18:01 by yettabaa          #+#    #+#             */
/*   Updated: 2022/10/24 00:48:15 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		r;
	char	t;

	t = c;
	r = ft_strlen(str) - 1;
	if (t == 0)
		return ((char *)(str + r + 1));
	while (r >= 0)
	{
		if (str[r] == t)
			return ((char *)(str + r));
		r--;
	}
	return (NULL);
}
