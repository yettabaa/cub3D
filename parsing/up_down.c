/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   up_down.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:14:10 by nfoughal          #+#    #+#             */
/*   Updated: 2023/06/15 19:14:34 by nfoughal         ###   ########.fr       */
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
		write(2, "Error: empty file44\n", 21);
		exit(1);
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
		write(2, "Error: empty line\n", 19);
		exit(1);
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
	fill_down_map(map + i, down_map, map);
	res->map = down_map;
	wall_check(down_map, map);
	if_valid(map + i, map);
}

int	up_and_down(char **map, int *i, int *count, t_map_result	*res)
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
		write(2, "Error: empty map\n", 18);
		exit(1);
	}
	return (0);
}
