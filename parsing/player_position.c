/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:40:09 by nfoughal          #+#    #+#             */
/*   Updated: 2023/06/17 02:48:30 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	duplicate_error(t_map_result *res)
{
	free(res->no);
	free(res->so);
	free(res->we);
	free(res->ea);
	free_array(res->map);
	write(2, "Error: duplacate symbol\n", 25);
	exit (1);
}

int	player_position(t_data *v)
{
	int	i;
	int	j;
	int k;

	i = 0;
	k = 0;
	while (v->pars.map[i])
	{
		j = 0;
		while (v->pars.map[i][j])
		{
			if ((v->pars.map[i][j] == '2' && (v->pars.map[i + 1][j] != '1' || v->pars.map[i - 1][j] != '1')) && (v->pars.map[i][j] == '2' && (v->pars.map[i][j + 1] != '1' || v->pars.map[i][j - 1] != '1')))
				duplicate_error(&v->pars); // erro
			// else if (v->pars.map[i][j] == '2' && v->pars.map[i][j + 1] != '1' && v->pars.map[i][j - 1] != '1')
			// 	duplicate_error(&v->pars);
			if (v->pars.map[i][j] == '3')
				_sprites(v, k++, i, j);
			j++;
		}
		i++;
	}
	return (1);
}

void	if_duplicate(t_data *v)
{
	int	i;
	int	j;
	int	count;
	// int count_sprites;

	i = 0;
	count = 0;
	v->count_sprites = 0;
	while (v->pars.map[i])
	{
		j = 0;
		while (v->pars.map[i][j])
		{
			(v->pars.map[i][j] == '3') && (v->count_sprites++);
			// if (v->pars.map[i][j] == 'S' || v->pars.map[i][j] == 'N'
			// || v->pars.map[i][j] == 'E' || v->pars.map[i][j] == 'W')
			if(ft_strchr("WSEN", v->pars.map[i][j]))
			{
				v->pars.y = i;
				v->pars.x = j;
				v->pars.palayer_dir = v->pars.map[i][j];
				count++;
			}
			j++;
		}
		i++;
	}
	if (count > 1)
		duplicate_error(&v->pars);
	// printf("%d\n", v->count_sprites);
	v->sprite = NULL;
	if (v->count_sprites)
	{
		v->sprite = malloc(sizeof(t_sprites) * v->count_sprites);
		if(!v->sprite)
			ft_error("Allocate t_sprites failed");
	}
}
