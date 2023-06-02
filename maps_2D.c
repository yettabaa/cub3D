/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_2D.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 01:50:02 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/02 02:47:28 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void steps(t_data *v)
{
    v->ryc.y_Hstp = v->scal;
    v->ryc.x_Hstp = 0;
    (v->ryc.ang != 0 && v->ryc.ang != 180) &&  (v->ryc.x_Hstp = v->scal / tan(rad(v->ryc.ang))); //tan +/-
    v->ryc.Hdelta = sqrt(pow(v->ryc.x_Hstp, 2) + pow(v->ryc.y_Hstp, 2));
    // printf("v->ryc.ang = %f  (x = %f, y = %f)\n", v->ryc.ang , v->x, v->y);
    v->ryc.var = (int)(v->y / v->scal);
    v->ryc.y_H1stp = (v->y - (v->ryc.var * v->scal)); // up
    (is(v, DOWN) || !v->ryc.y_H1stp) && (v->ryc.y_H1stp = ((v->ryc.var * v->scal + v->scal) - v->y)); // down
    v->ryc.x_H1stp = 0;
    (v->ryc.ang != 0 && v->ryc.ang != 180) && (v->ryc.x_H1stp = v->ryc.y_H1stp / tan(rad(v->ryc.ang)));
    v->ryc.DHside = sqrt(pow(v->ryc.x_H1stp, 2) + pow(v->ryc.y_H1stp, 2));
    // printf("x_H1stp = %f y_H1stp = %f x_Hstp = %f x_Hstp = %f\n", v->ryc.x_H1stp, v->ryc.y_H1stp, v->ryc.x_Hstp, v->ryc.y_Hstp);


    v->ryc.x_Vstp = v->scal;
    v->ryc.y_Vstp = v->scal * tan(rad(v->ryc.ang)); // tan vari +/-
    (v->ryc.ang == 90 || v->ryc.ang == 270) && (v->ryc.y_Vstp = 0);
    v->ryc.Vdelta = (sqrt(pow(v->ryc.x_Vstp, 2) + pow(v->ryc.y_Vstp, 2)));
    v->ryc.var = (v->x / v->scal); // can be in a varible // can initialized

    v->ryc.x_V1stp = v->x - v->ryc.var * v->scal; // left
    (is(v, RIGHT)) && (v->ryc.x_V1stp = (v->ryc.var * v->scal + v->scal) - v->x);
    (v->ryc.ang == 270 || v->ryc.ang == 90) && (v->ryc.x_V1stp = 0);
    v->ryc.y_V1stp = v->ryc.x_V1stp * tan(rad((v->ryc.ang)));
    v->ryc.DVside = (sqrt(fabs(pow(v->ryc.x_V1stp , 2)) + fabs(pow(v->ryc.y_V1stp, 2))));
     // printf("x_V1stp = %f y_V1stp = %f x_Vstp = %f x_Vstp = %f\n", v->x_V1stp, v->y_V1stp, v->x_Vstp, v->y_Vstp);
}



void player(t_data *v, int color)
{
    double vi;
    double frequency;
    
    disc(v, color);
    frequency = 60;
    vi = 0;
    v->x0 = 0;
    while (vi <= (frequency + v->epsilon))
    {
        // puts("---------------");
        // puts("---------------------------------\n");
        // printf("dda ==> (x = %f, y = %f) - (xf = %f, yf = %f\n", v->x, v->y, v->x_first, v->y_first);
        // if (vi == 0 || vi == 60)
        v->ryc.ang = normalize_angle_360(v->orientation -30 + vi);
        steps(v);
        
        // {
            // break;
        // vertical_intersections(v, normalize_angle_360(ang + vi));
        // printf("vi = %f ang  = %fng\n", vi, v->ang);
        // }
        // printf("x0 = %f vi = %f\n", v->x0, vi);
        horisontal_intersections(v); // rename
        rendering_wall(v);
        vi += (double)60 / (double)WIDTH;
        v->x0 += 1;
        // break;
    }
    // dda(v,0,100 ,100,30,0xffffff);
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
                rectangle(v, i * v->scal, j * v->scal, 0x0fff00ff);
            else if ((int)v->map[j][i] == 32)
                rectangle(v, i * v->scal, j * v->scal, 0);
            else
                rectangle(v, i * v->scal, j * v->scal, 0xffff00);
            dda(v, i * v->scal, j * v->scal, (i + 1) * v->scal, j * v->scal, 0xffffff);
            dda(v, i * v->scal, j * v->scal, i * v->scal, (j + 1) * v->scal, 0xffffff);      
        } 
    }
    player(v, 0xff);
}
