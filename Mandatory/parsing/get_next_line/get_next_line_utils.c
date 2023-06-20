/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:40:09 by nfoughal          #+#    #+#             */
/*   Updated: 2023/05/15 21:42:08 by nfoughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ftt_strdup(char *s1)
{
	char	*p;
	int		i;
	char	*str;

	str = (char *)s1;
	p = (char *) malloc(sizeof(char) * ftt_strlen(str) + 1);
	i = 0;
	if (!p)
		return (0);
	while (str[i])
	{
		p[i] = str[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ftt_strjoin(char *s1, char *s2)
{
	char	*p;
	int		i;
	int		j;

	if (!s1)
		s1 = ftt_strdup("");
	if (!s2)
		return (0);
	p = (char *) malloc (sizeof(char) * (ftt_strlen(s1) + ftt_strlen(s2)) + 1);
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
	free (s1);
	s1 = NULL;
	p[i] = '\0';
	return (p);
}

size_t	ftt_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		s++;
		i++;
	}
	return (i);
}

int	ftt_strchr(char *s, int c)
{
	if (!s)
		return (1);
	while (*s)
	{
		if (*s == (char)c)
			return (0);
		s++;
	}
	return (1);
}
