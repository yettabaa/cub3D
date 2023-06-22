/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 22:04:20 by nfoughal          #+#    #+#             */
/*   Updated: 2023/06/22 18:19:15 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	derection_name(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (!ft_strncmp((str + i), "NO ", 3))
		return (NO);
	if (!ft_strncmp(str + i, "SO ", 3))
		return (SO);
	if (!ft_strncmp(str + i, "WE ", 3))
		return (WE);
	if (!ft_strncmp(str + i, "EA ", 3))
		return (EA);
	if (!ft_strncmp(str + i, "F ", 2))
		return (FLOOR);
	if (!ft_strncmp(str + i, "C ", 2))
		return (CEIL);
	return (0);
}

void	split_and_check(char *str, t_map_result *res)
{
	int	i;

	i = 0;
	if (!derection_name(str))
		ft_error("Invalid map", "");
	else
	{
		while (str[i] && str[i] == ' ')
		i++;
		while (str[i] && str[i] != ' ')
		i++;
		if (derection_name(str) == SO)
			res->so = ft_strtrim(str + i, "\n ");
		else if (derection_name(str) == NO)
			res->no = ft_strtrim(str + i, "\n ");
		else if (derection_name(str) == WE)
			res->we = ft_strtrim(str + i, "\n ");
		else if (derection_name(str) == EA)
			res->ea = ft_strtrim(str + i, "\n ");
		else if (derection_name(str) == FLOOR)
			check_f_and_c (ft_strtrim(str + i, "\n "), res, 6);
		else if (derection_name(str) == CEIL)
			check_f_and_c (ft_strtrim(str + i, "\n "), res, 3);
	}
}

void	wall_check(char **map, char **array)
{
	int		i;

	i = 0;
	while (map[i])
	i++;
	first_and_last(map, i, array);
	check_sides(map, array);
}

void	parsing_bonus(t_data *v, int ac, char **av)
{
	char	**map;
	int		i;
	int		count;

	init_map(&v->pars);
	check_arg(ac, av);
	map = fill_array_map(av);
	count = 0;
	i = 0;
	if_empty(map);
	while (map[i])
	{
		while (map[i] && (ft_strlen(map[i]) == 1
				|| tab_spaces_checker(map[i]) == 1))
			i++;
		if (up_and_down(map, &i, &count, &v->pars))
			break ;
	}
	free_array(map);
	if (!v->pars.map)
		ft_error("map not found", "");
	check_null(&v->pars);
	if_duplicate_bonus(v);
	free_array(v->pars.map);
}
