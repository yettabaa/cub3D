/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 22:58:38 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/21 03:11:59 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	dda_sprite(t_data *v,t_object *object, double y0, double y1) // opti
{
    int		i;
    int x_texel;
    int y_texel;
	double	steps;
	unsigned int color;
   
	(y0 < 0) && (y0 = 0);
	(y1 > HIGHT) && (y1 = HIGHT);
	steps = fabs(y0 - y1);
	i = 0;
    (x_texel = v->txt.width * (v->x_wind - object->x0) / object->Diemension);
    (x_texel < 0) && (x_texel = 0);
    (x_texel > v->txt.width) && (x_texel = v->txt.width);
	while (i < steps)
	{
        y_texel = v->txt.height * (i + (fabs(v->y1 - v->y0 - steps) / 2)) / fabs(v->y1 - v->y0);
        (y_texel < 0) && (y_texel = 0);
        (y_texel > v->txt.height) && (y_texel = v->txt.height);
		color = v->txt.buff[y_texel * (v->txt.line / 4) + x_texel];
		((color >> 24 & 0x000000ff) != 255) && my_mlx_pixel_put(v ,v->x_wind, y0, color);
		y0++;
		i++;
	}
}

t_object *visible_sprite(t_data *v)
{
    int i;
    double ang;
    t_object *visible_sprite;
    
    i = -1;
    visible_sprite = NULL;
    while (++i < v->sprt.count_sprites)
    {
        ang = fabs((normalize_angle_360(v->orientation) - normalize_angle_360(Deg(atan2(v->sprite[i].ys - v->y, v->sprite[i].xs - v->x)))));
        (ang > 330) && (ang -= 330);
        if (ang <= 30)
            addobjt(&visible_sprite, newsprite(v, v->sprite[i]));
    }
    return(visible_sprite);
}

void render_ssprite(t_data *v, t_object *object)
{
    (v->sprt.frames == 7 * WIDTH + 1) && (v->sprt.frames = 0);
    (v->sprt.frames == 7 * WIDTH) && (v->sprt.ind_sprite_text += 1);
    (v->sprt.ind_sprite_text == 5) && (v->sprt.ind_sprite_text = 0);
    fill_sprite(v, v->sprt.ind_sprite_text % 5);
    v->sprt.frames += 1;
    v->y0 = object->y0;
	v->y1 = object->y1;
    if(v->x_wind >= object->x0  && v->x_wind <= object->x1)
	    dda_sprite(v,object, v->y0, v->y1);
}

void sprite_disc(t_data *v, double x, double y, int color)
{
    double x0;
    double y0;
    double radius;

    radius = v->scal / 3;
    y0 = -radius;
    while (y0 <= radius)
    {
        x0 = -radius;
        while (x0 <= radius)
        {
			if (round(x0 + x) >= 0 && round(x0 + x) < WIDTH && round(y0 + y) >= 0 && round(y0 + y) < HIGHT)
            	if ((x0 * x0) + y0 * y0 <= radius * radius)
                	my_mlx_pixel_put(v, x0 + x, y0 + y, color);
            x0++;
        }
        y0++;
    }
}

void render_sprite_MiniMap(t_data *v, t_object *sprites)
{
    t_object *hold;

    hold = sprites;
    while (hold)
    {
        if (hold->x + v->MiniMap.trans_x >= 0 && hold->x + v->MiniMap.trans_x < WIDTH && hold->y+ v->MiniMap.trans_y >= 0 && hold->y+ v->MiniMap.trans_y < HIGHT)
            sprite_disc(v, hold->x + v->MiniMap.trans_x, hold->y+ v->MiniMap.trans_y, 0xff0000);
        hold = hold->next;
    }
    
}