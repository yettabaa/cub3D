/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 22:04:20 by nfoughal          #+#    #+#             */
/*   Updated: 2023/06/21 04:39:19 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	if_args_true(char **split, t_map_result *res)
{
	int	i;

	i = 0;
	if (ft_strcmp(split[0], "NO") == 0 && res->no == NULL)
	res->no = split[1];
	else if (ft_strcmp(split[0], "SO") == 0 && res->so == NULL)
	res->so = split[1];
	else if (ft_strcmp(split[0], "WE") == 0 && res->we == NULL)
	res->we = split[1];
	else if (ft_strcmp(split[0], "EA") == 0 && res->ea == NULL)
	res->ea = split[1];
	else if (ft_strcmp(split[0], "F") == 0 && res->f == 0)
		check_f_and_c (split[1], res, 6, split);
	else if (ft_strcmp(split[0], "C") == 0 && res->c == 0)
		check_f_and_c (split[1], res, 3, split);
	else
	{
		free_array(split);
		write(2, "Error formula is incorrect\n", 28);
		exit(1);
	}
}

void	split_and_check(char *str, t_map_result *res)
{
	int		i;
	int		j;
	char	**split;

	i = 0;
	j = 0;
	split = split_spc_tab(str);
	while (split[i])
		i++;
	if (i != 2)
	{
		free_array(split);
		write(2, "Error Should be two arguments\n", 31);
		exit(1);
	}
	else
		if_args_true(split, res);
	free(split[0]);
	free(split);
}

void	wall_check(char **map, char **array)
{
	int		i;
	char	*str;

	i = 0;
	while (map[i])
	{
		str = ft_strtrim(map[i], " ");
		if (ft_strlen(str) == 1)
		{
			free(str);
			free_array(map);
			free_array(array);
			write(2, "Error: empty line\n", 19);
			exit(1);
		}
		free(str);
		i++;
	}
	first_and_last(map, i, array);
	check_sides(map, array);
}

void	parsing_bonus(t_data *v, int ac, char **av)
{
	char			**map;
	int				i;
	int				count;

	init_map(&v->pars);
	check_arg(ac, av);
	map = fill_array_map(av);
	i = 0;
	count = 0;
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
	// free_array(v->pars.map);
	if_duplicate_bonus(v);
}
