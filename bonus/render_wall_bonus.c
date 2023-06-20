/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 00:27:41 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/20 00:03:34 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
 // rename file
void texel_object(t_data *v) //raname and rplace to file of rendring
{
    double wall_hight;
	double ration;

    wall_hight = (v->scal / v->tmpobj->rydis_fbw) * v->ProjPlane; // indersta
    v->y0 = ((HIGHT) / 2) - (wall_hight / 2);
    v->y1 = v->y0 + wall_hight;
	if (v->tmpobj->type == DOOR && v->tmpobj->rydis_fbw < v->raydis_fishbowl)
	{
		ration = 1 - ((v->tmpobj->rydis- fmin(v->ryc.Vdelta, v->ryc.Hdelta)) / (2 * fmin(v->ryc.Vdelta, v->ryc.Hdelta))); //opening the door
		(ration - v->epsilon < 0) && (ration = 0);
		(ration + v->epsilon > 1) && (ration = 1);
		// printf("ang %f\n", normalize_angle_360(v->orientation));
		//  (printf("ration = %f  ryd_door = %f hdelta = %f\n", ration, v->door->raydis_door, v->ryc.Hdelta));
		fill_door(v, (ration + v->epsilon) * 32);
    	dda_door(v, v->y0, v->y1);
		
	}
	else if (v->tmpobj->type == SPRITE && v->tmpobj->rydis_fbw < v->raydis_fishbowl)
		render_ssprite(v);
	else 
		dda_textures(v, v->y0, v->y1, TEXT);
}

void render_objects(t_data *v) //raname and rplace to file of rendring
{
	t_object *tmp;
	t_object tmp_v2;
	
	while (v->tmpobj)
	{
		tmp = v->tmpobj;
		while (tmp)
		{
			if (v->tmpobj->rydis_fbw < tmp->rydis_fbw)
			{
				ft_memmove(&tmp_v2, tmp , sizeof(t_object) - sizeof(void *));
				ft_memmove(tmp, v->tmpobj , sizeof(t_object) - sizeof(void *));
				ft_memmove(v->tmpobj, &tmp_v2, sizeof(t_object) - sizeof(void *));
			}
			tmp = tmp->next;
		}
		texel_object(v);
		// printf("type %d ryd = %f\n", v->tmpobj->type, v->tmpobj->rydis);
		v->tmpobj = v->tmpobj->next;
	}
	v->object = NULL; //clear
}

void render_wall_bonus(t_data *v, double ang)
{
    double wall_hight;

    
    wall_hight = (v->scal / v->raydis_fishbowl) * v->ProjPlane;
    v->y0 = ((HIGHT) / 2) - (wall_hight / 2);
    v->y1 = v->y0 + wall_hight;
    if ((is(v, ang, UP) || (int)v->ryc.ang == 180) && v->txt.hitWall == HORI) 
        fill_textures(v, NO);
    else if ((is(v, ang, DOWN) ) && v->txt.hitWall == HORI) 
        fill_textures(v, SO);
    else if (is(v, ang, LEFT) && v->txt.hitWall == VER)
        fill_textures(v, EA);
    else if ((is(v, ang, RIGHT)) && v->txt.hitWall == VER) 
        fill_textures(v, WE);
	v->tmpobj = v->object;
    dda_textures(v, v->y1, HIGHT, FLOOR);
    dda_textures(v, 0, v->y0, CEIL);
    render_objects(v); // rename
    // clear_door(&v->list_door); //rename 
}