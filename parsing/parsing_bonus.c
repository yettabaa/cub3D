/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 05:43:38 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/19 03:50:11 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	player_position(t_data *v)
{
	int	j;
	int	i;
	int k;

	j = 0;
	k = 0;
	while (v->pars.map[j])
	{
		i = 0;
		while (v->pars.map[j][i])
		{
			if ((v->pars.map[j][i] == '2' && (v->pars.map[j + 1][i] != '1' || v->pars.map[j - 1][i] != '1')) && (v->pars.map[j][i] == '2' && (v->pars.map[j][i + 1] != '1' || v->pars.map[j][i - 1] != '1')))
				duplicate_error(&v->pars); // erro
			if (v->pars.map[j][i] == '3')
				_sprites(v, k++, i, j);
			i++;
		}
		j++;
	}
	v->pars.i = i;
	v->pars.j = j;
	return (1);
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
	// free_array(map);
	if_duplicate(v);
	// player_position(v);
}