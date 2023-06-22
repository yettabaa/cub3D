/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:28:01 by nfoughal          #+#    #+#             */
/*   Updated: 2023/06/22 04:39:18 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (0);
	p = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	i = 0;
	j = 0;
	if (!p)
		return (NULL);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		p[i] = s2[j];
		j++;
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
	char	*p;
	int		i;
	int		j;

	if (!s1 || !s2 || !s3)
		return (0);
	p = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2))
			+ ft_strlen(s3) + 1);
	i = 0;
	j = 0;
	if (!p)
		return (NULL);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	while (s2[j])
		p[i++] = s2[j++];
	j = 0;
	while (s3[j])
		p[i++] = s3[j++];
	p[i] = '\0';
	return (p);
}
