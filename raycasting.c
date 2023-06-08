/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 03:22:31 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/08 04:17:44 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void steps(t_data *v)
{
    t_steps step;
    
    step.y_Hstp = v->scal;
    step.x_Hstp = 0;
    (v->ryc.ang != 0 && v->ryc.ang != 180) &&  (step.x_Hstp = v->scal / tan(rad(v->ryc.ang))); //tan +/-
    v->ryc.Hdelta = (sqrt(pow(step.x_Hstp, 2) + pow(step.y_Hstp, 2)));
    // printf("v-v->ryc.ang = %f  (x = %f, y = %f)\n", v->ryc.ang , v->x, v->y);
    
    step.var = floor(v->y / v->scal);
    step.y_H1stp = (v->y - (step.var * v->scal)); // up
    (is(v, DOWN) || !step.y_H1stp) && (step.y_H1stp = ((step.var * v->scal + v->scal) - v->y)); // down
    step.x_H1stp = 0;
    (v->ryc.ang != 0 && v->ryc.ang != 180) && (step.x_H1stp = step.y_H1stp / tan(rad(v->ryc.ang)));
    v->ryc.DHside = (sqrt(pow(step.x_H1stp, 2) + pow(step.y_H1stp, 2)));
    

    step.x_Vstp = v->scal;
    step.y_Vstp = v->scal * tan(rad(v->ryc.ang)); // tan vari +/-
    (v->ryc.ang == 90 || v->ryc.ang == 270) && (step.y_Vstp = 0);
    v->ryc.Vdelta = (sqrt(pow(step.x_Vstp, 2) + pow(step.y_Vstp, 2)));

    step.var = floor(v->x / v->scal); // can be in a varible // can initialized
    step.x_V1stp = (v->x - step.var * v->scal); // left
    (is(v, RIGHT)) && (step.x_V1stp = ((step.var * v->scal + v->scal) - v->x));
    (v->ryc.ang == 270 || v->ryc.ang == 90) && (step.x_V1stp = 0);
    step.y_V1stp = (step.x_V1stp * tan(rad((v->ryc.ang))));
    v->ryc.DVside = (sqrt(fabs(pow(step.x_V1stp , 2)) + fabs(pow(step.y_V1stp, 2))));
    
}

void visualize_maps_1(t_data *v, int *i, int *j)
{
    *i = v->ryc.x1 / v->scal;
    *j = v->ryc.y1 / v->scal;
    (is(v, LEFT)) && (*i = ((v->ryc.x1) - v->epsilon) / v->scal);
    (is(v, RIGHT)) && (*i = (v->ryc.x1 + v->epsilon) / v->scal);
    ((is(v, UP) || (int)v->ryc.ang == 180)) && (*j = (v->ryc.y1 - v->epsilon) / v->scal);
    ((is(v, DOWN) || !(int)v->ryc.ang)) && (*j = ((v->ryc.y1) + v->epsilon) / v->scal);
}

void inc_smal_steps(t_data *v)
{
    int i;
    int j;
    int iq;
    double smal_sidstp;

    (v->ryc.Vdelta <= v->ryc.Hdelta) && (smal_sidstp = v->ryc.DVside);
    (v->ryc.Vdelta > v->ryc.Hdelta) && (smal_sidstp = v->ryc.DHside);
    v->ryc.x1 = v->x + (smal_sidstp * cos(rad(v->ryc.ang)));
    v->ryc.y1 = v->y + (smal_sidstp * sin(rad(v->ryc.ang)));
    visualize_maps_1(v, &i, &j);
    v->ryc.smal_stp = smal_sidstp;
    iq = 1;
    // printf("(smal_steps = %f) (i = %d, j = %d) (x/s = %f, y/s = %f) iq = %d (x = %f, y = %f) \n",v->ryc.smal_stp,i,j,v->ryc.x1 / v->scal, v->ryc.y1 / v->scal,iq, v->ryc.x1, v->ryc.y1);
    while ((int)v->pars.map[j][i] != '1')
    {
        v->ryc.smal_stp = iq * fmin(v->ryc.Hdelta, v->ryc.Vdelta) + smal_sidstp;
        v->ryc.x1 = v->x + (v->ryc.smal_stp * cos(rad(v->ryc.ang)));
        v->ryc.y1 = v->y + (v->ryc.smal_stp * sin(rad(v->ryc.ang)));
        visualize_maps_1(v, &i, &j);
        iq++;
        // printf("(smal_steps = %f) (i = %d, j = %d) (x/s = %f, y/s = %f) iq = %d (x = %f, y = %f) \n",v->ryc.smal_stp,i,j,v->ryc.x1 / v->scal, v->ryc.y1 / v->scal, iq, v->ryc.x1, v->ryc.y1);
    }
}

void inc_big_steps(t_data *v)
{
    int i;
    int j;
    int iq;
    double big_sidstp;
    
    (v->ryc.Vdelta <= v->ryc.Hdelta) && (big_sidstp = v->ryc.DHside);
    (v->ryc.Vdelta > v->ryc.Hdelta) && (big_sidstp = v->ryc.DVside);
    v->ryc.x1 = v->x + (big_sidstp * cos(rad(v->ryc.ang)));
    v->ryc.y1 = v->y + (big_sidstp * sin(rad(v->ryc.ang)));
    visualize_maps_1(v, &i, &j);
    v->ryc.big_stp = (big_sidstp);
    iq = 1;
    // printf("(big_step = %f) (i = %d, j = %d) (x/s = %f, y/s = %f) iq = %d (x = %f, y = %f) \n",v->ryc.big_stp,i,j,v->ryc.x1 / v->scal, v->ryc.y1 / v->scal,iq, v->ryc.x1, v->ryc.y1);
    while (big_sidstp < v->ryc.smal_stp && (int)v->pars.map[j][i] != '1')
    {
        v->ryc.big_stp = iq * fmax(v->ryc.Hdelta, v->ryc.Vdelta) + big_sidstp;
        v->ryc.x1 = v->x + (v->ryc.big_stp * cos(rad(v->ryc.ang)));
        v->ryc.y1 = v->y + (v->ryc.big_stp * sin(rad(v->ryc.ang)));
        visualize_maps_1(v, &i, &j);
        iq++;
        // printf("(big_step = %f) (i = %d, j = %d) (x/s = %f, y/s = %f) iq = %d (x = %f, y = %f) \n",v->ryc.big_stp, i, j, v->ryc.x1 / v->scal, v->ryc.y1 / v->scal,iq, v->ryc.x1, v->ryc.y1);
        if (v->ryc.big_stp > v->ryc.smal_stp || (int)v->pars.map[j][i] == '1')
            break;
    }
}

void raycasting(t_data *v)
{
    steps(v);
    inc_smal_steps(v);
    inc_big_steps(v);
    // printf("(DVside = %f, DHside = %f)\n",v->ryc.DVside,v->ryc.DHside);
    // printf("(Vdelta = %f, Hdelta = %f)\n",v->ryc.Vdelta,v->ryc.Hdelta);
    // printf("big %f small %f\n", v->ryc.big_stp, v->ryc.smal_stp);
    v->raydis = fmin(v->ryc.smal_stp, v->ryc.big_stp);// * cos(rad(v->orientation - v->ryc.ang)); // fixing fishbowl
    // ((fmin(v->ryc.smal_stp, v->ryc.big_stp) == v->ryc.smal_stp && v->ryc.Hdelta >= v->ryc.Vdelta) || (fmin(v->ryc.smal_stp, v->ryc.big_stp) == v->ryc.big_stp && v->ryc.Hdelta <= v->ryc.Vdelta)) && (v->hitWall = VER);
    // ((fmin(v->ryc.smal_stp, v->ryc.big_stp) == v->ryc.smal_stp && v->ryc.Hdelta <= v->ryc.Vdelta) || (fmin(v->ryc.smal_stp, v->ryc.big_stp) == v->ryc.big_stp && v->ryc.Hdelta >= v->ryc.Vdelta)) &&  (v->hitWall = HORI);
    if (v->ryc.big_stp > v->ryc.smal_stp && v->ryc.Hdelta > v->ryc.Vdelta + v->epsilon)
        v->hitWall = VER;
    else if (v->ryc.big_stp < v->ryc.smal_stp && v->ryc.Hdelta + v->epsilon < v->ryc.Vdelta)
        v->hitWall = VER;
    else if (v->ryc.big_stp > v->ryc.smal_stp && v->ryc.Hdelta + v->epsilon < v->ryc.Vdelta)
        v->hitWall = HORI;
    else if (v->ryc.big_stp < v->ryc.smal_stp && v->ryc.Hdelta > v->ryc.Vdelta+ v->epsilon)
        v->hitWall = HORI;
    // else 
    //     v->hitWall = 40;    
    // else if (v->ryc.big_stp == v->ryc.smal_stp && v->ryc.Hdelta == v->ryc.Vdelta)
    //     v->hitWall = VER;
    
    v->ryc.x1 = v->x + (v->raydis * cos(rad(v->ryc.ang))); //translation with distace of adjacent
    v->ryc.y1 = v->y + (v->raydis * sin(rad(v->ryc.ang))); //translation with distace of opposite
}