/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_2D.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 01:50:02 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/22 05:51:20 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	trans(t_data *v, double i, double j)
{
	v->minimap.trans_x = (WIDTH / 2) - v->x - 650;
	v->minimap.trans_y = v->minimap.raduis - v->y + 750;
	v->minimap.x = i + v->minimap.trans_x;
	v->minimap.y = j + v->minimap.trans_y;
}

void	maps_2d(t_data *v)
{
	int	i;
	int	j;

	j = -1;
	while ((int)v->pars.map2[(int)(++j / v->scal)])
	{
		i = -1;
		while ((int)v->pars.map2[(int)(j / v->scal)][(int)(++i / v->scal)])
		{
			trans(v, i, j);
			if (((i - v->x) * (i - v->x)) + ((j - v->y) * (j
						- v->y)) <= v->minimap.raduis * v->minimap.raduis)
			{
				if ((int)v->pars.map2[(int)(j / v->scal)][(int)(i
						/ v->scal)] == '1')
					my_pixel_put(v, v->minimap.x, v->minimap.y, 0);
				else if ((int)v->pars.map2[(int)(j / v->scal)][(int)(i
							/ v->scal)] == '2')
					my_pixel_put(v, v->minimap.x, v->minimap.y, 0xff);
				else if ((int)v->pars.map2[(int)(j / v->scal)][(int)(i
							/ v->scal)] != 32)
					my_pixel_put(v, v->minimap.x, v->minimap.y, 0xffffff);
			}
		}
	}
}

void	mini_maps(t_data *v, int color)
{
	double	vi;
	double	frequency;

	disc(v, 0x009DDF, v->minimap.raduis - 1);
	maps_2d(v);
	disc(v, color, v->scal / 3);
	frequency = 60;
	vi = 0;
	while (vi <= (frequency + v->epsil))
	{
		v->ryc.ang = normalize_angle_360(v->orientation - 30 + vi);
		raycasting(v, v->ryc.ang);
		dda(v, v->x + v->minimap.trans_x, v->y + v->minimap.trans_y, color);
		vi += 0.1;
	}
}
