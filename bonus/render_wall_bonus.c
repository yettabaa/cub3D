/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 00:27:41 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/17 02:42:18 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
 // rename file
void render_wall_bonus(t_data *v, double ang)
{
    double disProj;
    double wall_hight;

    
    disProj = (WIDTH / 2) / tan(rad(30));
    wall_hight = (v->scal / v->raydis_fishbowl) * disProj;
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
    dda_textures(v, v->y1, HIGHT, FLOOR);
    dda_textures(v, 0, v->y0, CEIL);
    render_door(v); // rename
    clear_door(&v->list_door); //rename 
    // dda_textures(v, v->y1, HIGHT, FLOOR);
    // dda_textures(v, 0, v->y0, CEIL);
}