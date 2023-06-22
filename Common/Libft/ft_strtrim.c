/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:19:49 by nfoughal          #+#    #+#             */
/*   Updated: 2023/06/22 04:40:14 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	spaces_checker(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

static char	*ft_subs(char const *s, unsigned int l, size_t m)
{
	char				*p;
	unsigned int		j;
	unsigned int		k;

	if (!s)
		return (0);
	j = 0;
	k = (m - l);
	p = (char *) malloc(sizeof(char) * k + 2);
	if (!p)
		return (0);
	while (s[l] != '\0' && (j <= k))
	{
		p[j] = s[l];
		l++;
		j++;
	}
	p[j] = '\0';
	return (p);
}

static int	ftchar(const char *str, int c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		l;
	char	*str;

	if (!s1 || !set)
		return (0);
	if (spaces_checker((char *)s1))
		return (ft_strdup(""));
	l = ft_strlen(s1);
	i = 0;
	l--;
	while (ftchar((char *)set, s1[i]) == 1)
		i++;
	while ((ftchar((char *)set, s1[l]) == 1))
		l--;
	if (l < i)
		return (ft_strdup(""));
	str = ft_subs(s1, i, l);
	return (str);
}
