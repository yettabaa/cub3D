/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_2D.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 01:50:02 by yettabaa          #+#    #+#             */
/*   Updated: 2023/05/23 02:10:15 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
typedef double t_deg;
typedef double t_rad;

t_rad	rad(t_deg angle)
{
	return (angle * (M_PI / 180));
}

// void vertical_intersections()
void horisontal_intersections(t_data *v, char angof_vue)
{
    // find first inter
    // find ystep
    // find xstep
    int xstep;
    int ystep;
    int i;
    int j;
    // convert to i,j
    //if intersection hit a wall
    // v->y_first = (v->y / v->scal * v->scal) + v->y;
    v->y_first = v->y - (v->y / v->scal);
    // printf("v->y_first %f v->y %f v->y / v->scal %f\n",v->y_first,v->y, (round(v->y / v->scal) * v->scal));
    v->x_first = v->x - (v->x + ((v->y - v->y_first) / tan(rad(angof_vue))));
    ystep = v->scal;
    xstep = ystep / tan(rad(angof_vue));
    v->x_first -= v->x;
    v->y_first -= v->y;
    j = round((v->y_first - (v->scal / 2)) / v->scal);
    i = round((v->x_first - (v->scal / 2)) / v->scal);
    printf("i = %d j = %d\n", i, j);
    printf("xstep = %d ystep = %d\n", xstep, ystep);
    // printf("x_first = %d ystep = %d\n", xstep, ystep);
    while ((int)v->map[j][i] != '1')
    {
        v->x_first -= xstep;
        v->y_first -= ystep;
        j = round((v->y_first - (v->scal / 2)) / v->scal);
        i = round((v->x_first - (v->scal / 2)) / v->scal);
    }
}

void player(t_data *v, int color)
{
    // int x1;
    // int y1;
    // int distance = 100;
    int frequency = 60;
    int vi = 0;
    int ang;
    
    disc(v, color);
    ang = v->angle - 180 -30;
    while (vi < frequency)
    {
        // x1 = v->x + (distance * cos(rad(ang + vi))); //translation with distace of adjacent
        // y1 = v->y + (distance * sin(rad(ang + vi++))); //translation with distace of opposite
        // dda(v, v->x, v->y, x1, y1, color);
        horisontal_intersections(v, ang + vi++);
        dda(v, v->x, v->y, v->x_first, v->y_first, color);
    }
}

void maps_2d(t_data *v)
{
    int i;
    int j;
    
    j = -1;
    while (v->map[++j])
    {
        i = -1;
        while (v->map[j][++i])
        {
            if ((int)v->map[j][i] == '1')
                rectangle(v, i * v->scal, j * v->scal, 0xff);
            else if ((int)v->map[j][i] == 32)
                rectangle(v, i * v->scal, j * v->scal, 0);
            else
                rectangle(v, i * v->scal, j * v->scal, 0xffffff);
            dda(v, i * v->scal, j * v->scal, (i + 1) * v->scal, j * v->scal, 0);
            dda(v, i * v->scal, j * v->scal, i * v->scal, (j + 1) * v->scal, 0);      
        } 
    }
    player(v, 0xff0000);
}