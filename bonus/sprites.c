/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 22:58:38 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/22 19:50:10 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	dda_sprite(t_data *v, t_object *object, double y0, double y1)
{
	int				i;
	int				x_texel;
	int				y_texel;
	double			steps;
	unsigned int	color;

	(y0 < 0) && (y0 = 0);
	(y1 > HIGHT) && (y1 = HIGHT);
	steps = fabs(y0 - y1);
	i = 0;
	(x_texel = v->tx.width * (v->x_wind - object->x0) / object->diemension);
	(x_texel < 0) && (x_texel = 0);
	(x_texel > v->tx.width) && (x_texel = v->tx.width);
	while (i < steps)
	{
		y_texel = v->tx.height * (i + (fabs(v->y1 - v->y0 - steps) / 2))
			/ fabs(v->y1 - v->y0);
		(y_texel < 0) && (y_texel = 0);
		(y_texel > v->tx.height) && (y_texel = v->tx.height);
		color = v->tx.buff[y_texel * (v->tx.line / 4) + x_texel];
		((color >> 24 & 0x000000ff) != 255) && my_pixel_put(v, v->x_wind, y0,
				color);
		y0++;
		i++;
	}
}

t_object	*visible_sprite(t_data *v)
{
	int			i;
	double		ang;
	t_object	*visible_sprite;

	i = -1;
	visible_sprite = NULL;
	while (++i < v->sprt.count_sprites)
	{
		ang = fabs((normalize_angle_360(v->orientation)
					- normalize_angle_360(_deg(atan2(v->sprite[i].ys - v->y,
								v->sprite[i].xs - v->x)))));
		(ang > 330) && (ang -= 330);
		if (ang <= 30)
			addobjt(&visible_sprite, newsprite(v, v->sprite[i]));
	}
	return (visible_sprite);
}

void	render_ssprite(t_data *v, t_object *object)
{
	(v->sprt.frames == 5 * WIDTH + 1) && (v->sprt.frames = 0);
	(v->sprt.frames == 5 * WIDTH) && (v->sprt.ind_sprite_text += 1);
	(v->sprt.ind_sprite_text == 5) && (v->sprt.ind_sprite_text = 0);
	fill_sprite(v, v->sprt.ind_sprite_text % 5);
	v->sprt.frames += 1;
	v->y0 = object->y0;
	v->y1 = object->y1;
	if (v->x_wind >= object->x0 && v->x_wind <= object->x1)
		dda_sprite(v, object, v->y0, v->y1);
}

void	sprite_disc(t_data *v, double x, double y, int color)
{
	double	x0;
	double	y0;
	double	radius;

	radius = v->scal / 3;
	y0 = -radius;
	while (y0 <= radius)
	{
		x0 = -radius;
		while (x0 <= radius)
		{
			if ((x0 * x0) + y0 * y0 <= radius * radius)
				my_pixel_put(v, x0 + x, y0 + y, color);
			x0++;
		}
		y0++;
	}
}

void	render_sprite_minimap(t_data *v, t_object *sprites)
{
	t_object	*hold;

	hold = sprites;
	while (hold)
	{
		if (hold->rydis_fbw < v->minimap.raduis)
			sprite_disc(v, hold->x + v->minimap.trans_x, hold->y
				+ v->minimap.trans_y, 0xff0000);
		hold = hold->next;
	}
}
