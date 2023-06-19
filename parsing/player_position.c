/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:40:09 by nfoughal          #+#    #+#             */
/*   Updated: 2023/06/18 19:20:31 by yettabaa         ###   ########.fr       */
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



void	if_duplicate(t_data *v)
{
	int	i;
	int	j;
	int	count;

	j = 0;
	count = 0;
	v->count_sprites = 0;
	while (v->pars.map[j])
	{
		i = 0;
		while (v->pars.map[j][i])
		{
			(v->pars.map[j][i] == '3') && (v->count_sprites++);
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
