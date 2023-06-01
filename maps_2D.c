/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_2D.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 01:50:02 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/01 01:57:06 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void steps(t_data *v)
{
    v->y_Hstp = v->scal;
    v->x_Hstp = 0;
    (v->ang != 0 && v->ang != 180) &&  (v->x_Hstp = v->scal / tan(rad(v->ang))); //tan +/-
    v->Hdelta = sqrt(pow(v->x_Hstp, 2) + pow(v->y_Hstp, 2));
    // printf("v->ang = %f  (x = %f, y = %f)\n", v->ang , v->x, v->y);
    v->var = (int)(v->y / v->scal);
    v->y_H1stp = (v->y - (v->var * v->scal)); // up
    (is(v, DOWN) || !v->y_H1stp) && (v->y_H1stp = ((v->var * v->scal + v->scal) - v->y)); // down
    v->x_H1stp = 0;
    (v->ang != 0 && v->ang != 180) && (v->x_H1stp = v->y_H1stp / tan(rad(v->ang)));
    v->DHside = sqrt(pow(v->x_H1stp, 2) + pow(v->y_H1stp, 2));
    // printf("x_H1stp = %f y_H1stp = %f x_Hstp = %f x_Hstp = %f\n", v->x_H1stp, v->y_H1stp, v->x_Hstp, v->y_Hstp);


    v->x_Vstp = v->scal;
    v->y_Vstp = v->scal * tan(rad(v->ang)); // tan vari +/-
    (v->ang == 90 || v->ang == 270) && (v->y_Vstp = 0);
    v->Vdelta = sqrt(pow(v->x_Vstp, 2) + pow(v->y_Vstp, 2));
    v->var = (v->x / v->scal); // can be in a varible // can initialized

    v->x_V1stp = v->x - v->var * v->scal; // left
    (is(v, RIGHT)) && (v->x_V1stp = (v->var * v->scal + v->scal) - v->x);
    (v->ang == 270 || v->ang == 90) && (v->x_V1stp = 0);
    v->y_V1stp = v->x_V1stp * tan(rad((v->ang)));
    v->DVside = sqrt(fabs(pow(v->x_V1stp , 2)) + fabs(pow(v->y_V1stp, 2)));
     // printf("x_V1stp = %f y_V1stp = %f x_Vstp = %f x_Vstp = %f\n", v->x_V1stp, v->y_V1stp, v->x_Vstp, v->y_Vstp);
}



void player(t_data *v, int color)
{
    double vi;
    double frequency;
    
    disc(v, color);
    frequency = 60;
    vi = 0;
    while (vi <= (frequency + v->epsilon))
    {
        // puts("---------------");
        // puts("---------------------------------\n");
        // printf("dda ==> (x = %f, y = %f) - (xf = %f, yf = %f\n", v->x, v->y, v->x_first, v->y_first);
        // if (vi == 0 || vi == 60)
        v->ang = normalize_angle_360(v->orientation -30 + vi);
        // {
        steps(v);
        horisontal_intersections(v);
            // break;
        // vertical_intersections(v, normalize_angle_360(ang + vi));
        dda(v, v->x, v->y, v->x1, v->y1, color);
        // printf("vi = %f ang  = %fng\n", vi, v->ang);
        // }
        vi += 0.1;
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
                rectangle(v, i * v->scal, j * v->scal, 0xffffff);
            dda(v, i * v->scal, j * v->scal, (i + 1) * v->scal, j * v->scal, 0);
            dda(v, i * v->scal, j * v->scal, i * v->scal, (j + 1) * v->scal, 0);      
        } 
    }
    player(v, 0xff);
}
