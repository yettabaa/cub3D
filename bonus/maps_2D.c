/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_2D.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 01:50:02 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/21 02:02:15 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void trans(t_data *v, double i, double j)
{
    v->MiniMap.trans_x = (WIDTH / 2) - v->x - 650;
    v->MiniMap.trans_y = v->MiniMap.raduis - v->y + 750;
    v->MiniMap.x = i + v->MiniMap.trans_x; 
    v->MiniMap.y = j + v->MiniMap.trans_y; 
}

void maps_2d(t_data *v)
{
    int i;
    int j;
    
    j = 0;
    while ((int)v->pars.map2[(int)(j / v->scal)])
    {
        i = 0;
        while ((int)v->pars.map2[(int)(j / v->scal)][(int)(i / v->scal)])
        {
            trans(v, i, j);
            if (((i - v->x) * (i - v->x)) + ((j - v->y) * (j - v->y)) <= v->MiniMap.raduis * v->MiniMap.raduis)
            {
                if ((int)v->pars.map2[(int)(j / v->scal)][(int)(i / v->scal)] == '1')
                    my_mlx_pixel_put(v, v->MiniMap.x, v->MiniMap.y, 0);
                else if ((int)v->pars.map2[(int)(j / v->scal)][(int)(i / v->scal)] == '2')
                    my_mlx_pixel_put(v, v->MiniMap.x, v->MiniMap.y, 0xff);
                else if ((int)v->pars.map2[(int)(j / v->scal)][(int)(i / v->scal)] != 32)
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
    
    disc(v, 0x009DDF, v->MiniMap.raduis - 1);
    maps_2d(v);
    disc(v, color, v->scal/3);
    frequency = 60;
    vi = 0;
    while (vi <= (frequency + v->epsilon))
    {
        v->ryc.ang = normalize_angle_360(v->orientation -30 + vi);
        raycasting(v, v->ryc.ang);
        dda(v, v->x + v->MiniMap.trans_x, v->y + v->MiniMap.trans_y, color);  // round to int for handle the corner in 2d
        vi += 0.1;
    }
}

