/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   up_down.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:14:10 by nfoughal          #+#    #+#             */
/*   Updated: 2023/06/22 18:17:35 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	if_empty(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	i++;
	if (i == 0)
	{
		free_array(map);
		ft_error("empty file44", "");
	}
}

void	fill_down_map(char **map, char **new, char **array)
{
	int	i;
	int	j;

	i = 0;
	while (map[i] && ft_strlen(map[i]) != 1)
	{
		j = 0;
		new[i] = malloc(sizeof(char) * (ft_strlen(map[i]) + 1));
		if (!new[i])
			ft_error("malloc failed", "");
		while (map[i][j] && map[i][j] != '\n')
		{
			new[i][j] = map[i][j];
			j++;
		}
		new[i][j] = '\0';
		i++;
	}
	new[i] = NULL;
	if (map[i] && ft_strlen(map[i]) == 1)
	{
		free_array(array);
		free_array(new);
		ft_error("Invalid data", "");
	}
}

void	go_down(char **map, int i, t_map_result	*res)
{
	int		j;
	char	**down_map;

	j = 0;
	while ((map + i)[j])
		j++;
	down_map = malloc(sizeof(char *) * (j + 1));
	if (down_map == NULL)
		ft_error("malloc failed", "");
	fill_down_map(map + i, down_map, map);
	res->map = down_map;
	wall_check(down_map, map);
	if_valid(map + i, map, res);
}

int	up_and_down(char **map, int *i, int *count, t_map_result *res)
{
	if (map[*i])
	{
		if (*count < 6)
			split_and_check(map[*i], res);
		if (*count >= 6)
		{
			go_down(map, (*i), res);
			return (1);
		}
		(*count)++;
		(*i)++;
	}
	else
	{
		free_array(map);
		ft_error("empty map", "");
	}
	return (0);
}
