/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:08:27 by nfoughal          #+#    #+#             */
/*   Updated: 2023/06/05 22:27:19 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_0_pos(char *str, char **array, int y, char **map)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '0')
		{
			if (check_directions(map, y, i) == 0)
			{
				free_array(map);
				free_array(array);
				write(2, "Error: map is not valid\n", 25);
				exit(1);
			}
		}
		i++;
	}
}

int	re_long_line(char **map)
{
	int	i;
	int	j;
	size_t	len;

	j = 0;
	i = 1;
	len = ft_strlen(map[0]);
	while (map[i])
	{
		if (ft_strlen(map[i]) > len)
			len = ft_strlen(map[i]);
		i++;
	}
	return (len);
}

void	fill_spaces(char **p, int row, char **map)
{
	int	i;
	int	len;

	i = 0;
	len = re_long_line(map) - 1;
	while (i < row)
	{
		p[i] = malloc(sizeof(char) * (len + 1));
		p[i] = ft_memset(p[i], ' ', len);
		p[i][len] = '\0';
		i++;
	}
	p[i] = NULL;
}

void	map_copy(char **p, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (p[i])
	{
		j = 0;
		while (map[i][j] && map[i][j] != '\n')
		{
			p[i][j] = map[i][j];
			j++;
		}
		i++;
	}
}

void	if_valid(char **map, char **array)
{
	int		i;
	int		row;
	char	**p;

	i = 1;
	row = 0;
	while (map[row])
		row++;
	p = malloc(sizeof(char *) * (row + 1));
	fill_spaces(p, row, map);
	map_copy(p, map);
	while (i < row)
	{
		check_0_pos(map[i], array, i, p);
		i++;
	}
	free_array(p);
}
