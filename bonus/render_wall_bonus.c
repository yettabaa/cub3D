/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 00:27:41 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/22 05:51:07 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	texel_object(t_data *v, t_object *object)
{
	double	wall_hight;
	double	ration;

	wall_hight = (v->scal / object->rydis_fbw) * v->projplane;
	v->y0 = ((HIGHT) / 2) - (wall_hight / 2);
	v->y1 = v->y0 + wall_hight;
	if (object->type == DOOR && object->rydis_fbw < v->raydis_fishbowl)
	{
		ration = 1 - ((object->rydis - fmin(v->ryc.vdelta, v->ryc.hdelta)) / (2
					* fmin(v->ryc.vdelta, v->ryc.hdelta)));
		(ration - v->epsil < 0) && (ration = 0);
		(ration + v->epsil > 1) && (ration = 1);
		fill_door(v, (ration + v->epsil) * 32);
		dda_door(v, object, v->y0, v->y1);
	}
	else if (object->type == SPRITE && object->rydis_fbw < v->raydis_fishbowl)
		render_ssprite(v, object);
	else
		dda_textures(v, v->y0, v->y1, TEXT);
}

void	render_objects(t_data *v, t_object *object)
{
	t_object	*tmp;
	t_object	tmp_v2;

	while (object)
	{
		tmp = object;
		while (tmp)
		{
			if (object->rydis_fbw < tmp->rydis_fbw)
			{
				ft_memmove(&tmp_v2, tmp, sizeof(t_object) - sizeof(void *));
				ft_memmove(tmp, object, sizeof(t_object) - sizeof(void *));
				ft_memmove(object, &tmp_v2, sizeof(t_object) - sizeof(void *));
			}
			tmp = tmp->next;
		}
		texel_object(v, object);
		object = object->next;
	}
}

void	render_wall_bonus(t_data *v, t_object *object, double ang)
{
	double	wall_hight;

	wall_hight = (v->scal / v->raydis_fishbowl) * v->projplane;
	v->y0 = ((HIGHT) / 2) - (wall_hight / 2);
	v->y1 = v->y0 + wall_hight;
	if ((is(v, ang, UP) || (int)v->ryc.ang == 180) && v->tx.hitw == HORI)
		fill_textures(v, NO);
	else if ((is(v, ang, DOWN)) && v->tx.hitw == HORI)
		fill_textures(v, SO);
	else if (is(v, ang, LEFT) && v->tx.hitw == VER)
		fill_textures(v, EA);
	else if ((is(v, ang, RIGHT)) && v->tx.hitw == VER)
		fill_textures(v, WE);
	dda_textures(v, v->y1, HIGHT, FLOOR);
	dda_textures(v, 0, v->y0, CEIL);
	render_objects(v, object);
}
