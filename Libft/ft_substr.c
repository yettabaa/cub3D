/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 22:13:20 by nfoughal          #+#    #+#             */
/*   Updated: 2022/10/30 14:53:15 by nfoughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	j;

	j = 0;
	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len + start > ft_strlen(s))
		p = (char *) malloc(sizeof(char) * ft_strlen(s) - start + 1);
	else
		p = (char *) malloc(sizeof(char) * (len + 1));
	if (!p)
		return (0);
	while (j < len && s[start])
	{
		p[j] = s[start];
		start++;
		j++;
	}
	p[j] = '\0';
	return (p);
}
