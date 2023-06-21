/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:40:09 by nfoughal          #+#    #+#             */
/*   Updated: 2023/06/20 20:54:06 by nfoughal         ###   ########.fr       */
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

void	if_duplicate_bonus(t_data *v)
{
	int	i;
	int	j;
	int	count;

	j = -1;
	count = 0;
	v->sprt.count_sprites = 0;
	while (v->pars.map[++j])
	{
		i = -1;
		while (v->pars.map[j][++i])
		{
			(v->pars.map[j][i] == '3') && (v->sprt.count_sprites++);
			if (ft_strchr("WSEN", v->pars.map[j][i]))
			{
				v->pars.y = j;
				v->pars.x = i;
				v->pars.palayer_dir = v->pars.map[j][i];
				count++;
			}
		}
	}
	if (count > 1)
		duplicate_error(&v->pars);
}
