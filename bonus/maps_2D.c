/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_2D.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 01:50:02 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/19 05:48:53 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"





void trans(t_data *v, double i, double j)
{
    v->MiniMap.trans_x = (WIDTH / 2) - v->x - 650;
    v->MiniMap.trans_y = v->MiniMap.raduis - v->y + 750;
    // v->MiniMap.transz_x = v->MiniMap.trans_x - v->x;
    // v->MiniMap.transz_y = v->MiniMap.trans_y - v->y;
    // printf("tx = %f ty = %f\n", v->m.trans_x, v->m.trans_y);
    v->MiniMap.x = i + v->MiniMap.trans_x; 
    v->MiniMap.y = j + v->MiniMap.trans_y; 
}

void maps_2d(t_data *v)
{
    int i;
    int j;
    
    j = 0;
    while (j < v->pars.j * v->scal)
    {
        i = 0;
        while (i < v->pars.i * v->scal)
        {
            trans(v, i, j);
            // if (((i + v->m.transz_x) * (i + v->m.transz_x)) + (j + v->m.transz_y) * (j + v->m.transz_y) <= 200 * 200)
            if (((i - v->x) * (i - v->x)) + ((j - v->y) * (j - v->y)) <= v->MiniMap.raduis * v->MiniMap.raduis)
            {
                
                if ((int)v->pars.map[(int)(j / v->scal)][(int)(i / v->scal)] == '1')
                    my_mlx_pixel_put(v, v->MiniMap.x, v->MiniMap.y, 0);
                else if ((int)v->pars.map[(int)(j / v->scal)][(int)(i / v->scal)] == '2')
                    my_mlx_pixel_put(v, v->MiniMap.x, v->MiniMap.y, 0xff0000);
                else if ((int)v->pars.map[(int)(j / v->scal)][(int)(i / v->scal)] == '3')
                    my_mlx_pixel_put(v, v->MiniMap.x, v->MiniMap.y, 0x00ff00);
                else    
                    my_mlx_pixel_put(v, v->MiniMap.x, v->MiniMap.y, 0xffffff);
            }  
            i++;
        }
        j++;
    }
}

void mini_maps(t_data *v, int color)
{
    double vi;
    double frequency;
    
    maps_2d(v);
    disc(v, v->x + v->MiniMap.trans_x, v->y + v->MiniMap.trans_y, color);
    frequency = 60;
    vi = 0;
    while (vi <= (frequency + v->epsilon))
    {
        // puts("---------------------------------\n");
        v->ryc.ang = normalize_angle_360(v->orientation -30 + vi);
        raycasting_bonus(v, v->ryc.ang);
        // if (((v->x) * (v->x)) + ((v->y) * (v->y)) <= v->MiniMap.raduis * v->MiniMap.raduis)
        dda(v, v->x + v->MiniMap.trans_x, v->y + v->MiniMap.trans_y, color);  // round to int for handle the corner in 2d
        // if (vi == 30)
        // {
        //     dda(v, v->x, v->y, 0xff0000);  // round to int for handle the corner in 2d
        //     dda(v, v->x, v->y, 0xff0000);  // round to int for handle the corner in 2d
        //     dda(v, v->x, v->y, 0xff0000);  // round to int for handle the corner in 2d

        // }
            
        vi += 0.1;
    }
}

