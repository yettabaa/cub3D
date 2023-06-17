/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 23:47:25 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/17 16:10:19 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	dda_door(t_data *v, double y0, double y1) // opti
{
	int		i;
    int x_texel;
    int y_texel;
	double	yinc;
	double	steps;
	unsigned int color;
   
	(y0 < 0) && (y0 = 0);
	(y1 > HIGHT) && (y1 = HIGHT);
	steps = fabs(y0 - y1);
	yinc = (y1 - y0) / steps;
	i = 0;
    (v->list_door->hitw == VER) && (x_texel = v->txt.width * fmod(v->list_door->y , v->scal) / v->scal);
    (v->list_door->hitw == HORI) && (x_texel = v->txt.width * fmod(v->list_door->x , v->scal) / v->scal);
	while (i < steps)
	{
        y_texel = v->txt.height * (i + (fabs(v->y1 - v->y0 - steps) / 2)) / fabs(v->y1 - v->y0);
		color = v->txt.buff[y_texel * (v->txt.line / 4) + x_texel];
		if (round(v->x_wind) >= 0 && round(v->x_wind) < WIDTH && round(y0) >= 0 && round(y0) < HIGHT)
			((color >> 24 & 0x000000ff) != 255) && my_mlx_pixel_put(v ,(v->x_wind), (y0), color);
		y0 = y0 + yinc;
		i++;
	}
}

void text_door(t_data *v) //raname and rplace to file of rendring
{
	// double disProj;
    double wall_hight;
	double ration;

    // disProj = (WIDTH / 2) / tan(Rad(30));
    wall_hight = (v->scal / v->list_door->rydis_fbw) * v->disProj; // indersta
    v->y0 = ((HIGHT) / 2) - (wall_hight / 2);
    v->y1 = v->y0 + wall_hight;
	if (v->list_door->type == DOOR && v->list_door->rydis_fbw < v->raydis_fishbowl)
	{
		// ration = 1 - (raycasting(v, v->orientation, '2')) / (3 * fmin(v->ryc.Vdelta, v->ryc.Hdelta));
		ration = 1 - ((v->list_door->rydis- fmin(v->ryc.Vdelta, v->ryc.Hdelta)) / (2 * fmin(v->ryc.Vdelta, v->ryc.Hdelta)));
		(ration - v->epsilon < 0) && (ration = 0);
		(ration + v->epsilon > 1) && (ration = 1);
		// printf("ang %f\n", normalize_angle_360(v->orientation));
		//  (printf("ration = %f  ryd_door = %f hdelta = %f\n", ration, v->door->raydis_door, v->ryc.Hdelta));
		fill_door(v, (ration + v->epsilon) * 32);
    	dda_door(v, v->y0, v->y1);
		
	}
	else
		dda_textures(v, v->y0, v->y1, TEXT);
}

void render_door(t_data *v) //raname and rplace to file of rendring
{
	t_list_door *tmp;
	t_list_door tmp_v2;

	while (v->list_door)
	{
		tmp = v->list_door;
		while (tmp)
		{
			if (v->list_door->rydis_fbw < tmp->rydis_fbw)
			{
				ft_memmove(&tmp_v2, tmp , sizeof(t_list_door) - sizeof(void *));
				ft_memmove(tmp, v->list_door , sizeof(t_list_door) - sizeof(void *));
				ft_memmove(v->list_door, &tmp_v2, sizeof(t_list_door) - sizeof(void *));
			}
			tmp = tmp->next;
		}
		text_door(v);
		v->list_door = v->list_door->next;
	}
	v->list_door = NULL;
}