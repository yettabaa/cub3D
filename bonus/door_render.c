/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 23:47:25 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/18 05:07:27 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	dda_door(t_data *v, double y0, double y1) // opti calcule
{
	int		i;
    int x_texel;
    int y_texel;
	// double	yinc;
	double	steps;
	unsigned int color;
   
	(y0 < 0) && (y0 = 0);
	(y1 > HIGHT) && (y1 = HIGHT);
	steps = fabs(y0 - y1);
	// yinc = (y1 - y0) / steps;
	i = 0;
    (v->object->hitw == VER) && (x_texel = v->txt.width * fmod(v->object->y , v->scal) / v->scal);
    (v->object->hitw == HORI) && (x_texel = v->txt.width * fmod(v->object->x , v->scal) / v->scal);
	while (i < steps)
	{
        y_texel = v->txt.height * (i + (fabs(v->y1 - v->y0 - steps) / 2)) / fabs(v->y1 - v->y0);
		color = v->txt.buff[y_texel * (v->txt.line / 4) + x_texel];
		if (v->x_wind >= 0 && v->x_wind < WIDTH && round(y0) >= 0 && round(y0) < HIGHT)
			((color >> 24 & 0x000000ff) != 255) && my_mlx_pixel_put(v ,(v->x_wind), (y0), color);
		// y0 = y0 + yinc;
		y0++;
		i++;
	}
}

void text_door(t_data *v) //raname and rplace to file of rendring
{
    double wall_hight;
	double ration;

    wall_hight = (v->scal / v->object->rydis_fbw) * v->disProj; // indersta
    v->y0 = ((HIGHT) / 2) - (wall_hight / 2);
    v->y1 = v->y0 + wall_hight;
	if (v->object->type == DOOR && v->object->rydis_fbw < v->raydis_fishbowl)
	{
		ration = 1 - ((v->object->rydis- fmin(v->ryc.Vdelta, v->ryc.Hdelta)) / (2 * fmin(v->ryc.Vdelta, v->ryc.Hdelta))); //opening the door
		(ration - v->epsilon < 0) && (ration = 0);
		(ration + v->epsilon > 1) && (ration = 1);
		// printf("ang %f\n", normalize_angle_360(v->orientation));
		//  (printf("ration = %f  ryd_door = %f hdelta = %f\n", ration, v->door->raydis_door, v->ryc.Hdelta));
		fill_door(v, (ration + v->epsilon) * 32);
    	dda_door(v, v->y0, v->y1);
		
	}
	else if (v->object->type == SPRITE && v->object->rydis_fbw < v->raydis_fishbowl)
		render_ssprite(v);
	else 
		dda_textures(v, v->y0, v->y1, TEXT);
}

void render_object(t_data *v) //raname and rplace to file of rendring
{
	t_object *tmp;
	t_object tmp_v2;

	while (v->object)
	{
		tmp = v->object;
		while (tmp)
		{
			if (v->object->rydis_fbw < tmp->rydis_fbw)
			{
				ft_memmove(&tmp_v2, tmp , sizeof(t_object) - sizeof(void *));
				ft_memmove(tmp, v->object , sizeof(t_object) - sizeof(void *));
				ft_memmove(v->object, &tmp_v2, sizeof(t_object) - sizeof(void *));
			}
			tmp = tmp->next;
		}
		text_door(v);
		// printf("type %d ryd = %f\n", v->object->type, v->object->rydis);
		v->object = v->object->next;
	}
	// exit(0);
	v->object = NULL;
}