/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 22:12:26 by nfoughal          #+#    #+#             */
/*   Updated: 2023/06/20 16:29:56 by nfoughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_count_char(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\t' && str[i] != ' ' && str[i] != '\n' && str[i])
		i++;
	return (i);
}

char	*ft_strdap(char *str)
{
	int		count;
	int		i;
	char	*p;

	count = ft_count_char(str);
	i = 0;
	p = malloc(sizeof(char) * (count + 1));
	if (!p)
		ft_error("Error\n");
	while (i < count)
	{
		p[i] = str[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

int	count_word(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n')
		str++;
	while (*str)
	{
		count++;
		while (*str != '\t' && *str != ' ' && *str != '\n' && *str)
			str++;
		while (*str == '\t' || *str == ' ' || *str == '\n')
			str++;
	}
	return (count);
}

void	fill_array(char **array, char *str)
{
	int	i;
	int	count;

	i = 0;
	count = count_word(str);
	while (*str == ' ' || *str == '\t')
		str++;
	while (*str)
	{
		array[i] = ft_strdap(str);
		while (*str != '\t' && *str != ' ' && *str != '\n' && *str)
			str++;
		while (*str == '\t' || *str == ' ' || *str == '\n')
			str++;
		i++;
	}
}

char	**split_spc_tab(char *str)
{
	int		count;
	char	**array;

	count = count_word(str);
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		ft_error("Error\n");
	fill_array(array, str);
	array[count] = 0;
	return (array);
}
