/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 22:58:38 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/20 03:58:35 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_object *newsprite(t_data *v, t_GetSprites sprite)
{
    t_object *node;
	double FOV_angle ;
	double ProjP_sprite;
    
    node = malloc(sizeof(t_object));
    if (!node)
        ft_error("Allocate new door failed");
	node->type = SPRITE;
	FOV_angle = Deg(atan2(sprite.ys - v->y, sprite.xs - v->x)) - (v->orientation);
	ProjP_sprite = tan(Rad(FOV_angle)) * v->ProjPlane;
    node->x = sprite.xs;
    node->y = sprite.ys;
	node->rydis_fbw = des_betw_2pt(sprite.xs, sprite.ys, v->x, v->y) * cos(Rad(FOV_angle));
	node->Diemension = (v->scal / node->rydis_fbw) * v->ProjPlane;
	node->y0 = (HIGHT / 2) - (node->Diemension / 2);
	node->y1 = node->y0 + node->Diemension;
	node->x0 = (WIDTH / 2) + ProjP_sprite - (node->Diemension / 2);
	node->x1 = node->x0 + node->Diemension;
	// printf("x = %f y = %f ryd = %f\n", sprite.xs, sprite.ys, node->rydis_fbw);
	node->next = NULL;
    return(node);
}

void	dda_sprite(t_data *v, double y0, double y1, int x) // opti
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
    (x_texel = v->txt.width * (x - v->tmpobj->x0) / v->tmpobj->Diemension);
	while (i < steps)
	{
        y_texel = v->txt.height * (i + (fabs(v->y1 - v->y0 - steps) / 2)) / fabs(v->y1 - v->y0);
		color = v->txt.buff[y_texel * (v->txt.line / 4) + x_texel];
		if (x >= 0 && x < WIDTH && round(y0) >= 0 && round(y0) < HIGHT)
			((color >> 24 & 0x000000ff) != 255) && my_mlx_pixel_put(v ,x, y0, color);
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

void render_ssprite(t_data *v)
{
    (v->sprt.frames == 4 * WIDTH + 1) && (v->sprt.frames = 0);
    (v->sprt.frames == 4 * WIDTH) && (v->sprt.ind_sprite_text += 1);
    (v->sprt.ind_sprite_text == 4) && (v->sprt.ind_sprite_text = 0);
    fill_sprite(v, v->sprt.ind_sprite_text % 4);
    v->sprt.frames += 1;
    v->y0 = v->tmpobj->y0;
	v->y1 = v->tmpobj->y1;
    if(v->x_wind >= v->tmpobj->x0  && v->x_wind <= v->tmpobj->x1)
	    dda_sprite(v, v->y0, v->y1, v->x_wind);
}

void render_sprite_MiniMap(t_data *v, t_object *sprites)
{
    t_object *hold;

    hold = sprites;
    while (hold)
    {
        if (hold->x + v->MiniMap.trans_x >= 0 && hold->x + v->MiniMap.trans_x < WIDTH && hold->y+ v->MiniMap.trans_y >= 0 && hold->y+ v->MiniMap.trans_y < HIGHT)
            disc(v, hold->x + v->MiniMap.trans_x, hold->y+ v->MiniMap.trans_y, 0xff0000, v->scal/3);
        hold = hold->next;
    }
    
}