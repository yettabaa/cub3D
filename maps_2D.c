/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_2D.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 01:50:02 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/07 05:16:43 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void maps_2d(t_data *v)
{
    int i;
    int j;
    
    j = -1;
    while (v->pars.map[++j])
    {
        i = -1;
        while (v->pars.map[j][++i])
        {
            if ((int)v->pars.map[j][i] == '0')
                rectangle(v, i * v->scal, j * v->scal, 0xffab00);
            else if ((int)v->pars.map[j][i] == '1')
                rectangle(v, i * v->scal, j * v->scal, 0x00ab00);
            // dda(v, i * v->scal, j * v->scal, (i + 1) * v->scal, j * v->scal, 0xffffff);
            // dda(v, i * v->scal, j * v->scal, i * v->scal, (j + 1) * v->scal, 0xffffff);      
        } 
    }
}

void mini_maps(t_data *v, int color)
{
    double vi;
    double frequency;
    
    maps_2d(v);
    disc(v, color);
    frequency = 60;
    vi = 0;
    while (vi <= (frequency + v->epsilon))
    {
        // puts("---------------------------------\n");
        v->ryc.ang = normalize_angle_360(v->orientation -30 + vi);
        raycasting(v);
        dda(v, v->x, v->y, 0xff);  // round to int for handle the corner in 2d
        vi += 0.1;
    }
}

void cube3D(t_data *v)
{
    double vi;
    double frequency;
    
    vi = 0;
    v->x0 = 0;
    frequency = 60;
    update(v);
    while (vi <= (frequency + v->epsilon))
    {
        // puts("---------------------------------\n");
        v->ryc.ang = normalize_angle_360(v->orientation -30 + vi);
        raycasting(v);
        rendering_wall(v);
        vi += (double)60 / (double)WIDTH;
        v->x0 += 1;
    }
    mini_maps(v, 0xff);
}