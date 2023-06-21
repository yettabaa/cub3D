/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:08:27 by nfoughal          #+#    #+#             */
/*   Updated: 2023/06/21 23:58:49 by nfoughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_0_pos(char *str, char **array, int y, char **map)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '0' || str[i] == 'N'
			|| str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
		{
			if (check_directions(map, y, i) == 0)
			{
				free_array(map);
				free_array(array);
				ft_error("map is not valid", "");
			}
		}
		i++;
	}
}

int	re_long_line(char **map)
{
	int		i;
	int		j;
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

void	fill_spaces(char **p, char **map, t_map_result *res)
{
	int	i;
	int	len;
	int	j;

	j = 0;
	len = re_long_line(map) - 1;
	res->i = len;
	while (map[j])
	{
		i = 0;
		p[j] = malloc(sizeof(char) * (len + 1));
		if (!p[j])
			ft_error("malloc failed", "");
		while (i < len)
		{
			if (i < (int)ft_strlen(map[j]) && map[j][i] && map[j][i] != '\n')
				p[j][i] = map[j][i];
			else
				p[j][i] = ' ';
			i++;
		}
		p[j][i] = '\0';
		j++;
	}
	p[j] = NULL;
}

void	if_valid(char **map, char **array, t_map_result *res)
{
	int		i;
	int		row;
	char	**p;

	i = 1;
	row = 0;
	while (map[row])
		row++;
	res->j = row;
	p = malloc(sizeof(char *) * (row + 1));
	if (!p)
		ft_error("malloc failed", "");
	fill_spaces(p, map, res);
	res->map2 = p;
	while (i < row)
	{
		check_0_pos(map[i], array, i, p);
		i++;
	}
}
