/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 00:46:21 by yettabaa          #+#    #+#             */
/*   Updated: 2022/10/26 18:03:53 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	i;
	int	len;

	if (!s1 || !set)
		return (NULL);
	i = -1;
	len = ft_strlen(s1);
	while (s1[++i])
		if (!ft_strchr(set, s1[i]))
			break ;
	while (--len)
		if (!ft_strchr(set, s1[len]))
			break ;
	return (ft_substr(s1, i, (len + 1) - i));
}
