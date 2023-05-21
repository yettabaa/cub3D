/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_2D.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 01:50:02 by yettabaa          #+#    #+#             */
/*   Updated: 2023/05/22 00:07:48 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
double	rad(double degree)
{
	return (degree * (M_PI / 180));
}
void player(t_data *v, int color)
{
    int x1;
    int y1;
    int distance = 100;
    int frequency = 60;
    int vi = 0;
    int ang;
    
    disc(v, color);
    // v->angle -= 30;
    ang = v->angle - 30;
    while (vi < frequency)
    {
        x1 = v->x + (distance * cos(rad(ang + vi)));
        y1 = v->y + (distance * sin(rad(ang + vi++)));
        dda(v, v->x, v->y, x1, y1, color);
    }   
}

// void ray()

void maps_2d(t_data *v)
{
    int i;
    int j;
    int x = 0;
    int y = 0;
    
    j = -1;
    while (v->map[++j])
    {
        i = -1;
        x = 0;
        while (v->map[j][++i])
        {
            if ((int)v->map[j][i] == '1')
                rectangle(v, x, y, 0xff);
            else if ((int)v->map[j][i] == 32)
                rectangle(v, x, y, 0);
            else 
                rectangle(v, x, y, 0xffffff);
            dda(v, i * v->surface, j * v->surface, (i + 1) * v->surface, j * v->surface, 0);
            dda(v, i * v->surface, j * v->surface, i * v->surface, (j + 1) * v->surface, 0);
            x += v->surface;        
        }
        y += v->surface;
    }
    player(v, 0xff0000);
}