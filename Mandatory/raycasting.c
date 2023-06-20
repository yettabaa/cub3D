/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 03:22:31 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/20 04:06:27 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void steps(t_data *v, double ang)
{
    t_steps step;
    
    step.y_Hstp = v->scal;
    step.x_Hstp = 0;
    (ang != 0 && ang != 180) &&  (step.x_Hstp = v->scal / tan(Rad(ang))); //tan +/-
    v->ryc.Hdelta = (sqrt(pow(step.x_Hstp, 2) + pow(step.y_Hstp, 2)));
    // printf("v-ang = %f  (x = %f, y = %f)\n", ang , v->x, v->y);
    
    step.var = floor(v->y / v->scal);
    step.y_H1stp = (v->y - (step.var * v->scal)); // up
    (is(v,ang, DOWN) || !step.y_H1stp) && (step.y_H1stp = ((step.var * v->scal + v->scal) - v->y)); // down
    step.x_H1stp = 0;
    (ang != 0 && ang != 180) && (step.x_H1stp = step.y_H1stp / tan(Rad(ang)));
    v->ryc.DHside = (sqrt(pow(step.x_H1stp, 2) + pow(step.y_H1stp, 2)));
    

    step.x_Vstp = v->scal;
    step.y_Vstp = v->scal * tan(Rad(ang)); // tan vari +/-
    (ang == 90 || ang == 270) && (step.y_Vstp = 0);
    v->ryc.Vdelta = (sqrt(pow(step.x_Vstp, 2) + pow(step.y_Vstp, 2)));

    step.var = floor(v->x / v->scal); // can be in a varible // can initialized
    step.x_V1stp = (v->x - step.var * v->scal); // left
    (is(v,ang, RIGHT)) && (step.x_V1stp = ((step.var * v->scal + v->scal) - v->x));
    (ang == 270 || ang == 90) && (step.x_V1stp = 0);
    step.y_V1stp = (step.x_V1stp * tan(Rad((ang))));
    v->ryc.DVside = (sqrt(fabs(pow(step.x_V1stp , 2)) + fabs(pow(step.y_V1stp, 2))));
    
}

void visualize_maps(t_data *v, double ang, int *i, int *j)
{
    *i = v->ryc.x / v->scal;
    *j = v->ryc.y / v->scal;
    (is(v, ang,LEFT)) && (*i = ((v->ryc.x) - v->epsilon) / v->scal);
    (is(v, ang, RIGHT)) && (*i = (v->ryc.x + v->epsilon) / v->scal);
    ((is(v, ang, UP) || (int)ang == 180)) && (*j = (v->ryc.y - v->epsilon) / v->scal);
    ((is(v, ang, DOWN) || !(int)ang)) && (*j = ((v->ryc.y) + v->epsilon) / v->scal);
}

static void inc_smal_steps(t_data *v, double ang)
{
    int i;
    int j;
    int iq;
    double smal_sidstp;

    (v->ryc.Vdelta <= v->ryc.Hdelta) && (smal_sidstp = v->ryc.DVside);
    (v->ryc.Vdelta > v->ryc.Hdelta) && (smal_sidstp = v->ryc.DHside);
    v->ryc.x = v->x + (smal_sidstp * cos(Rad(ang)));
    v->ryc.y = v->y + (smal_sidstp * sin(Rad(ang)));
    visualize_maps(v, ang, &i, &j);
    v->ryc.smal_stp = smal_sidstp;
    iq = 1;
    while (check_(v, i, j, WALL))
    {
        v->ryc.smal_stp = iq * fmin(v->ryc.Hdelta, v->ryc.Vdelta) + smal_sidstp;
        v->ryc.x = v->x + (v->ryc.smal_stp * cos(Rad(ang)));
        v->ryc.y = v->y + (v->ryc.smal_stp * sin(Rad(ang)));
        visualize_maps(v, ang, &i, &j);
        iq++;
    }
}

static void inc_big_steps(t_data *v, double ang)
{
    int i;
    int j;
    int iq;
    double big_sidstp;
    
    (v->ryc.Vdelta <= v->ryc.Hdelta) && (big_sidstp = v->ryc.DHside);
    (v->ryc.Vdelta > v->ryc.Hdelta) && (big_sidstp = v->ryc.DVside);
    v->ryc.x = v->x + (big_sidstp * cos(Rad(ang)));
    v->ryc.y = v->y + (big_sidstp * sin(Rad(ang)));
    visualize_maps(v,ang, &i, &j);
    v->ryc.big_stp = (big_sidstp);
    iq = 1;
    while (big_sidstp < v->ryc.smal_stp && check_(v, i, j, WALL))
    {
        v->ryc.big_stp = iq * fmax(v->ryc.Hdelta, v->ryc.Vdelta) + big_sidstp;
        v->ryc.x = v->x + (v->ryc.big_stp * cos(Rad(ang)));
        v->ryc.y = v->y + (v->ryc.big_stp * sin(Rad(ang)));
        visualize_maps(v,ang, &i, &j);
        iq++;
        if (v->ryc.big_stp > v->ryc.smal_stp || check_(v, i, j, 0))
            break;
    }
}

double raycasting(t_data *v, double ang)
{
    steps(v, ang);
    inc_smal_steps(v, ang);
    inc_big_steps(v, ang);
    v->raydis = fmin(v->ryc.smal_stp, v->ryc.big_stp);
    v->raydis_fishbowl = fmin(v->ryc.smal_stp, v->ryc.big_stp) * cos(Rad(v->orientation - ang));
    if (v->ryc.big_stp > v->ryc.smal_stp && v->ryc.Hdelta > v->ryc.Vdelta + v->epsilon)
        v->txt.hitWall = VER;
    else if (v->ryc.big_stp < v->ryc.smal_stp && v->ryc.Hdelta + v->epsilon < v->ryc.Vdelta)
        v->txt.hitWall = VER;
    else if (v->ryc.big_stp > v->ryc.smal_stp && v->ryc.Hdelta + v->epsilon < v->ryc.Vdelta)
        v->txt.hitWall = HORI;
    else if (v->ryc.big_stp < v->ryc.smal_stp && v->ryc.Hdelta > v->ryc.Vdelta+ v->epsilon)
        v->txt.hitWall = HORI;
    v->xw = v->x + (v->raydis * cos(Rad(ang))); //translation with distace of adjacent
    v->yw = v->y + (v->raydis * sin(Rad(ang))); //translation with distace of opposite
    return(v->raydis);
}