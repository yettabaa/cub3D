/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:00:41 by nfoughal          #+#    #+#             */
/*   Updated: 2022/10/30 15:19:37 by nfoughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = NULL;
	if (n == 0)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	while (i < n)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	**ft_freeall(char **list)
{
	size_t	j;

	j = 0;
	while (list[j])
	{
		free(list[j]);
		j++;
	}
	free(list);
	return (NULL);
}

size_t	count(char const *s, char c)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (s[i])
	{
		while ((s[i] != c) && ((s[i + 1] == c) || (s[i + 1] == '\0')))
		{
			j++;
			i++;
			if (s[i] == '\0')
				i--;
			break ;
		}
		i++;
	}
	return (j);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	i;
	size_t	k;
	size_t	size;

	i = 0;
	k = 0;
	if (!s)
		return (0);
	array = (char **)malloc(sizeof(char *) * (count(s, c) + 1));
	if (!array)
		return (NULL);
	while (i < count(s, c) && s[k] != '\0')
	{
		while (s[k] == c)
			k++;
		size = k;
		while (s[k] != c && s[k] != '\0')
			k++;
		array[i] = ft_strndup(&s[size], k - size);
		if (!array[i++])
			return (ft_freeall(array));
	}
	array[i] = NULL;
	return (array);
}
