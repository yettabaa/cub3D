/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_2D.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 01:50:02 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/17 18:53:52 by yettabaa         ###   ########.fr       */
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
            if ((int)v->pars.map[j][i] == '1')
                rectangle(v, i * v->scal, j * v->scal, 0);
            else if ((int)v->pars.map[j][i] == '2')
                rectangle(v, i * v->scal, j * v->scal, 0xff0000);
            else if ((int)v->pars.map[j][i] == '3')
                rectangle(v, i * v->scal, j * v->scal, 0x00ff00);
            else    
                rectangle(v, i * v->scal, j * v->scal, 0xffffff);
            // if ((int)v->pars.map[j][i] == '3')
            //     disc(v, (i * v->scal + v->scal / 2), j * v->scal + v->scal / 2, 0xff0000);
            // dda_old(v, i * v->scal, j * v->scal, (i + 1) * v->scal, j * v->scal, 0xffbb00);
            // dda_old(v, i * v->scal, j * v->scal, i * v->scal, (j + 1) * v->scal, 0xffbb00);      
        } 
    }
}

void mini_maps(t_data *v, int color)
{
    double vi;
    double frequency;
    
    maps_2d(v);
    disc(v, v->x, v->y, color);
    frequency = 60;
    vi = 0;
    while (vi <= (frequency + v->epsilon))
    {
        // puts("---------------------------------\n");
        v->ryc.ang = normalize_angle_360(v->orientation -30 + vi);
        raycasting_bonus(v, v->ryc.ang);
        dda(v, v->x, v->y, color);  // round to int for handle the corner in 2d
        if (vi == 30)
        {
            dda(v, v->x, v->y, 0xff0000);  // round to int for handle the corner in 2d
            dda(v, v->x, v->y, 0xff0000);  // round to int for handle the corner in 2d
            dda(v, v->x, v->y, 0xff0000);  // round to int for handle the corner in 2d

        }
            
        vi += 0.5;
    }
}

