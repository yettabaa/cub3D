/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_2D.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 01:50:02 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/04 00:07:58 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void steps(t_data *v)
{
    v->ryc.y_Hstp = v->scal;
    v->ryc.x_Hstp = 0;
    (v->ryc.ang != 0 && v->ryc.ang != 180) &&  (v->ryc.x_Hstp = v->scal / tan(rad(v->ryc.ang))); //tan +/-
    v->ryc.Hdelta = (sqrt(pow(v->ryc.x_Hstp, 2) + pow(v->ryc.y_Hstp, 2)));
    // printf("v->ryc.ang = %f  (x = %f, y = %f)\n", v->ryc.ang , v->x, v->y);
    
    v->ryc.var = floor(v->y / v->scal);
    v->ryc.y_H1stp = (v->y - (v->ryc.var * v->scal)); // up
    (is(v, DOWN) || !v->ryc.y_H1stp) && (v->ryc.y_H1stp = ((v->ryc.var * v->scal + v->scal) - v->y)); // down
    v->ryc.x_H1stp = 0;
    (v->ryc.ang != 0 && v->ryc.ang != 180) && (v->ryc.x_H1stp = v->ryc.y_H1stp / tan(rad(v->ryc.ang)));
    v->ryc.DHside = (sqrt(pow(v->ryc.x_H1stp, 2) + pow(v->ryc.y_H1stp, 2)));
    // printf("x_H1stp = %f y_H1stp = %f x_Hstp = %f x_Hstp = %f\n", v->ryc.x_H1stp, v->ryc.y_H1stp, v->ryc.x_Hstp, v->ryc.y_Hstp);


    v->ryc.x_Vstp = v->scal;
    v->ryc.y_Vstp = v->scal * tan(rad(v->ryc.ang)); // tan vari +/-
    (v->ryc.ang == 90 || v->ryc.ang == 270) && (v->ryc.y_Vstp = 0);
    v->ryc.Vdelta = (sqrt(pow(v->ryc.x_Vstp, 2) + pow(v->ryc.y_Vstp, 2)));

    v->ryc.var = floor(v->x / v->scal); // can be in a varible // can initialized
    v->ryc.x_V1stp = (v->x - v->ryc.var * v->scal); // left
    (is(v, RIGHT)) && (v->ryc.x_V1stp = ((v->ryc.var * v->scal + v->scal) - v->x));
    (v->ryc.ang == 270 || v->ryc.ang == 90) && (v->ryc.x_V1stp = 0);
    v->ryc.y_V1stp = (v->ryc.x_V1stp * tan(rad((v->ryc.ang))));
    v->ryc.DVside = (sqrt(fabs(pow(v->ryc.x_V1stp , 2)) + fabs(pow(v->ryc.y_V1stp, 2))));
    //  printf("x_V1stp = %f y_V1stp = %f x_Vstp = %f x_Vstp = %f\n", v->ryc.x_V1stp, v->ryc.y_V1stp, v->ryc.x_Vstp, v->ryc.y_Vstp);
}



void player(t_data *v)
{
    double vi;
    double frequency;
    
    frequency = 60;
    vi = 0;
    v->x0 = 0;
    while (vi <= (frequency + v->epsilon))
    {
        // puts("---------------------------------\n");
        v->ryc.ang = normalize_angle_360(v->orientation -30 + vi);
        steps(v);
        horisontal_intersections(v); // rename
        rendering_wall(v);
        vi += (double)60 / (double)WIDTH;
        v->x0 += 1;
    }
}

void mini_maps(t_data *v, int color)
{
    double vi;
    double frequency;
    
    disc(v, color);
    frequency = 60;
    vi = 0;
    while (vi <= (frequency + v->epsilon))
    {
        // puts("---------------------------------\n");
        v->ryc.ang = normalize_angle_360(v->orientation -30 + vi);
        steps(v);
        horisontal_intersections(v); // rename
        dda(v, v->x, v->y, (v->ryc.x1), (v->ryc.y1), 0xff);  // round to int for handle the corner in 2d
        vi += 0.1;
        // vi += (double)60 / (double)WIDTH;
    }
}

void maps_2d(t_data *v)
{
    int i;
    int j;
    
    player(v);
    j = -1;
    while (v->map[++j])
    {
        i = -1;
        while (v->map[j][++i])
        {
            if ((int)v->map[j][i] == '1')
                rectangle(v, i * v->scal, j * v->scal, 0x00ab00);
            else if ((int)v->map[j][i] == 32)
                rectangle(v, i * v->scal, j * v->scal, 0);
            else
                rectangle(v, i * v->scal, j * v->scal, 0xffab00);
            // dda(v, i * v->scal, j * v->scal, (i + 1) * v->scal, j * v->scal, 0xffffff);
            // dda(v, i * v->scal, j * v->scal, i * v->scal, (j + 1) * v->scal, 0xffffff);      
        } 
    }
    mini_maps(v, 0xff);
}
