/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_2D.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 01:50:02 by yettabaa          #+#    #+#             */
/*   Updated: 2023/05/23 20:17:21 by yettabaa         ###   ########.fr       */
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
void horisontal_intersections(t_data *v, int angof_vue)
{
    // find first inter
    // find ystep
    // find xstep
    // convert to i,j
    //if intersection hit a wall
    double xstep;
    double ystep;
    v->y_first = ((int)(v->y / v->scal) * v->scal);
    (angof_vue < 90) && (v->x_first = v->x + (((v->y - v->y_first) / tan(rad(angof_vue)))));
    (angof_vue > 90) && (v->x_first = v->x - (((v->y - v->y_first) / tan(rad(180 - angof_vue)))));
    (angof_vue == 90) && (v->x_first = v->x);
    // (angof_vue > 90) && (v->x_first = v->x - (((v->y - v->y_first) / tan(rad(angof_vue)))));
    printf("v->x_first %f v->x %f (v->x / v->scal) %f\n",v->x_first,v->x, ( ((v->y - v->y_first) / tan(rad(angof_vue)))));
    ystep = v->scal;
    (angof_vue < 90) && (xstep = v->scal / tan(rad(angof_vue)));
    (angof_vue > 90) && (xstep = v->scal / tan(rad(180 - angof_vue)));
    (angof_vue == 90) && (xstep = 0);
    printf("xstep = %f ystep = %f tan(%d)= %f\n", xstep, ystep,angof_vue, tan(rad(angof_vue)));
    printf("v->x_first = %f v->y_first = %f\n\n", v->x_first, v->y_first);
    // while ((int)v->map[j + 1][i] != '1')
    while ((int)v->map[(int)(v->y_first  / v->scal) - 1][(int)v->x_first  / v->scal] != '1')
    {   
        (angof_vue < 90) && (v->x_first += xstep);
        (angof_vue >= 90) && (v->x_first -= xstep);
        // (angof_vue > 90) && (v->x_first += xstep);
        v->y_first -= ystep;
        // printf("i = %u j = %u\n\n", (unsigned int)(v->x_first  / v->scal), (unsigned int)(v->y_first  / v->scal));
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
    ang = v->angle - 180 - 30;
    puts("---------------------------------");
    while (vi <= frequency)
    {
        // x1 = v->x + (distance * cos(rad(ang + vi))); //translation with distace of adjacent
        // y1 = v->y + (distance * sin(rad(ang + vi++))); //translation with distace of opposite
        // dda(v, v->x, v->y, x1, y1, color);
        printf("angle = %d angofvue %d\n", ang, ang + vi);
        horisontal_intersections(v, ang + vi);
        printf("dda ==> (x = %f, y = %f) - (xf = %f, yf = %f\n", v->x, v->y, v->x_first, v->y_first);
        dda(v, v->x, v->y, v->x_first, v->y_first, color);
        vi++;
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