/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 03:22:31 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/04 23:40:26 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

    (v->ryc.Vdelta <= v->ryc.Hdelta) && (v->ryc.smal_sidstp = v->ryc.DVside);
    (v->ryc.Vdelta > v->ryc.Hdelta) && (v->ryc.smal_sidstp = v->ryc.DHside);
    v->ryc.x1 = v->x + (v->ryc.smal_sidstp * cos(rad(v->ryc.ang)));
    v->ryc.y1 = v->y + (v->ryc.smal_sidstp * sin(rad(v->ryc.ang)));
    visualize_maps_1(v, &i, &j);
    v->ryc.smal_stp = v->ryc.smal_sidstp;
    iq = 1;
    // printf("(smal_steps = %f) (i = %d, j = %d) (x/s = %f, y/s = %f) iq = %d (x = %f, y = %f) \n",v->ryc.smal_stp,i,j,v->ryc.x1 / v->scal, v->ryc.y1 / v->scal,iq, v->ryc.x1, v->ryc.y1);
    while ((int)v->map[j][i] != '1')
    {
        v->ryc.smal_stp = (iq * fmin(v->ryc.Hdelta, v->ryc.Vdelta) + v->ryc.smal_sidstp);
        v->ryc.x1 = (v->x + (v->ryc.smal_stp * cos(rad(v->ryc.ang))));
        v->ryc.y1 = (v->y + (v->ryc.smal_stp * sin(rad(v->ryc.ang))));
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
    
    (v->ryc.Vdelta <= v->ryc.Hdelta) && (v->ryc.big_sidstp = v->ryc.DHside);
    (v->ryc.Vdelta > v->ryc.Hdelta) && (v->ryc.big_sidstp = v->ryc.DVside);
    v->ryc.x1 = (v->x + (v->ryc.big_sidstp * cos(rad(v->ryc.ang))));
    v->ryc.y1 = (v->y + (v->ryc.big_sidstp * sin(rad(v->ryc.ang))));
    visualize_maps_1(v, &i, &j);
    v->ryc.big_stp = (v->ryc.big_sidstp);
    iq = 1;
    // printf("(big_step = %f) (i = %d, j = %d) (x/s = %f, y/s = %f) iq = %d (x = %f, y = %f) \n",v->ryc.big_stp,i,j,v->ryc.x1 / v->scal, v->ryc.y1 / v->scal,iq, v->ryc.x1, v->ryc.y1);
    while (v->ryc.big_sidstp < v->ryc.smal_stp && (int)v->map[j][i] != '1')
    {
        v->ryc.big_stp = (iq * fmax(v->ryc.Hdelta, v->ryc.Vdelta) + v->ryc.big_sidstp);
        v->ryc.x1 = (v->x + (v->ryc.big_stp * cos(rad(v->ryc.ang))));
        v->ryc.y1 = (v->y + (v->ryc.big_stp * sin(rad(v->ryc.ang))));
        visualize_maps_1(v, &i, &j);
        iq++;
        // printf("(big_step = %f) (i = %d, j = %d) (x/s = %f, y/s = %f) iq = %d (x = %f, y = %f) \n",v->ryc.big_stp, i, j, v->ryc.x1 / v->scal, v->ryc.y1 / v->scal,iq, v->ryc.x1, v->ryc.y1);
        if (v->ryc.big_stp > v->ryc.smal_stp || (int)v->map[j][i] == '1')
            break;
    }
}
// TODO puts cos and sin in var
void horisontal_intersections(t_data *v)
{
    inc_smal_steps(v);
    inc_big_steps(v);
    // printf("(DVside = %f, DHside = %f)\n",v->ryc.DVside,v->ryc.DHside);
    // printf("(Vdelta = %f, Hdelta = %f)\n",v->ryc.Vdelta,v->ryc.Hdelta);
    // printf("big %f small %f\n", v->ryc.big_stp, v->ryc.smal_stp);
    v->raydis = (fmin(v->ryc.smal_stp, v->ryc.big_stp));
    v->ryc.x1 = (v->x + (v->raydis * cos(rad(v->ryc.ang)))); //translation with distace of adjacent
    v->ryc.y1 = (v->y + (v->raydis * sin(rad(v->ryc.ang)))); //translation with distace of opposite
}