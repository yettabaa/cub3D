/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 00:27:41 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/21 01:32:44 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
 // rename file
void texel_object(t_data *v, t_object *object) //raname and rplace to file of rendring
{
    double wall_hight;
	double ration;

    wall_hight = (v->scal / object->rydis_fbw) * v->ProjPlane; // indersta
    v->y0 = ((HIGHT) / 2) - (wall_hight / 2);
    v->y1 = v->y0 + wall_hight;
	if (object->type == DOOR && object->rydis_fbw < v->raydis_fishbowl)
	{
		ration = 1 - ((object->rydis- fmin(v->ryc.Vdelta, v->ryc.Hdelta)) / (2 * fmin(v->ryc.Vdelta, v->ryc.Hdelta))); //opening the door
		(ration - v->epsilon < 0) && (ration = 0);
		(ration + v->epsilon > 1) && (ration = 1);
		// printf("ang %f\n", normalize_angle_360(v->orientation));
		//  (printf("ration = %f  ryd_door = %f hdelta = %f\n", ration, v->door->raydis_door, v->ryc.Hdelta));
		fill_door(v, (ration + v->epsilon) * 32);
    	dda_door(v,object, v->y0, v->y1);
		
	}
	else if (object->type == SPRITE && object->rydis_fbw < v->raydis_fishbowl)
		render_ssprite(v, object);
	else 
		dda_textures(v, v->y0, v->y1, TEXT);
}

void render_objects(t_data *v, t_object *object) //raname and rplace to file of rendring
{
	t_object *tmp;
	// t_object *tmp2;
	t_object tmp_v2;
	
	// tmp2 = object;
	while (object)
	{
		tmp = object;
		while (tmp)
		{
			if (object->rydis_fbw < tmp->rydis_fbw)
			{
				ft_memmove(&tmp_v2, tmp , sizeof(t_object) - sizeof(void *));
				ft_memmove(tmp, object , sizeof(t_object) - sizeof(void *));
				ft_memmove(object, &tmp_v2, sizeof(t_object) - sizeof(void *));
			}
			tmp = tmp->next;
		}
		texel_object(v, object);
		// printf("type %d ryd = %f\n", v->tmpobj->type, v->tmpobj->rydis);
		object = object->next;
	}
	// clear_objt(&tmp2);
	// v->hold_objt = NULL; //clear
}

void render_wall_bonus(t_data *v,t_object *object, double ang)
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
	// object = v->hold_objt;
    dda_textures(v, v->y1, HIGHT, FLOOR);
    dda_textures(v, 0, v->y0, CEIL);
    render_objects(v, object); // rename
    
}