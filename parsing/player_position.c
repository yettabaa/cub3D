/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:40:09 by nfoughal          #+#    #+#             */
/*   Updated: 2023/06/17 17:03:58 by yettabaa         ###   ########.fr       */
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
			// else if (v->pars.map[j][i] == '2' && v->pars.map[j][i + 1] != '1' && v->pars.map[j][i - 1] != '1')
			// 	duplicate_error(&v->pars);
			if (v->pars.map[j][i] == '3')
				_sprites(v, k++, i, j);
			i++;
		}
		j++;
	}
	return (1);
}

void	if_duplicate(t_data *v)
{
	int	i;
	int	j;
	int	count;
	// int count_sprites;

	j = 0;
	count = 0;
	v->count_sprites = 0;
	while (v->pars.map[j])
	{
		i = 0;
		while (v->pars.map[j][i])
		{
			(v->pars.map[j][i] == '3') && (v->count_sprites++);
			// if (v->pars.map[j][i] == 'S' || v->pars.map[j][i] == 'N'
			// || v->pars.map[j][i] == 'E' || v->pars.map[j][i] == 'W')
			if(ft_strchr("WSEN", v->pars.map[j][i]))
			{
				v->pars.y = j;
				v->pars.x = i;
				v->pars.palayer_dir = v->pars.map[j][i];
				count++;
			}
			i++;
		}
		j++;
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
