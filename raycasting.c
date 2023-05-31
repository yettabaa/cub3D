/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 03:22:31 by yettabaa          #+#    #+#             */
/*   Updated: 2023/05/31 04:14:05 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void visualize_maps(t_data *v, int *i, int *j)
{
    int ang_nor;
    
    ang_nor = v->ang;
    // ang_nor = normalize_angle_360(v->ang);
    // *i = v->x1 / v->scal;
    // *j = v->y1 / v->scal;
    (is(v, LEFT)) && (*i = (v->x1 - 1) / v->scal);
    (is(v, RIGHT)) && (*i = (v->x1 + 1) / v->scal);
    (is(v, UP) || ang_nor == 180) && (*j = (v->y1 - 1) / v->scal);
    (is(v, DOWN) || !ang_nor) && (*j = (v->y1 + 1) / v->scal);
}

int is_wall(t_data *v, int inc, int flag)
{
    int ti;
    int tj;
    (void)flag;
    (is(v, LEFT) || v->ang == 270) && (ti = (v->x - 2) / v->scal);
    (is(v, RIGHT) || v->ang == 90) && (ti = (v->x + 2) / v->scal);
    (is(v, UP) || v->ang == 180) && (tj = (v->y - 2) / v->scal);
    (is(v, DOWN) || v->ang == 0) && (tj = (v->y + 2) / v->scal);
    if ((int)v->map[tj][ti] == '1')
        return (2);
    ti = (inc * cos(rad(v->ang))) / v->scal;
    tj = (inc * sin(rad(v->ang))) / v->scal;
    if ((int)v->map[tj][ti] == '1')
        return (1);
    return (0);
}

void inc_smal_steps(t_data *v)
{
    int i;
    int j;
    int iq;

    // puts("----------------");
    if (v->Vdelta <= v->Hdelta)
        v->smal_sidstp = v->DVside;
    else
        v->smal_sidstp = v->DHside;
    v->x1 = v->x + (v->smal_sidstp * cos(rad(v->ang))); // (1,5) angle 225
    v->y1 = v->y + (v->smal_sidstp * sin(rad(v->ang)));
    // printf("(x_p = %f ,y_p = %f) (x_ry = %f, y_ry = %f) DVside = %f DHside %f\n",v->x, v->y, v->x1, v->y1,v->DVside, v->DHside);
    visualize_maps(v, &i, &j);
    v->smal_stp = v->smal_sidstp;
    iq = 1;
    printf("v->ang = %f v->Smal_sidstp %f  (x = %f, y = %f) (i = %d, j = %d)\n",v->ang, v->smal_sidstp,v->x1,v->y1,i,j);
    while ((int)v->map[j][i] != '1')
    {
        printf("(smal_steps = %f) (i = %d, j = %d) (x/s = %f, y/s = %f) iq = %d (x = %f, y = %f) \n",v->smal_stp,i,j,v->x1 / v->scal, v->y1 / v->scal,iq, v->x1, v->y1);
        v->smal_stp = (iq * fmin(v->Hdelta, v->Vdelta) + v->smal_sidstp);
        v->x1 = v->x + (v->smal_stp * cos(rad(v->ang))); //translation with distace of adjacent
        v->y1 = v->y + (v->smal_stp * sin(rad(v->ang))); //translation with distace of opposite
        visualize_maps(v, &i, &j);
        iq++;
        printf("(smal_steps = %f) (i = %d, j = %d) (x/s = %f, y/s = %f) iq = %d (x = %f, y = %f) \n",v->smal_stp,i,j,v->x1 / v->scal, v->y1 / v->scal,iq, v->x1, v->y1);
    }
    
}

void inc_big_steps(t_data *v)
{
    int i;
    int j;
    int iq;
    
    if (v->Vdelta <= v->Hdelta)
        v->big_sidstp = v->DHside;
    else
        v->big_sidstp = v->DVside;
    // printf("(i = %d iz = %f, j = %d) \n",i, (v->y / v->scal), j);
    v->x1 = v->x + (v->big_sidstp * cos(rad(v->ang))); //translation with distace of adjacent
    v->y1 = v->y + (v->big_sidstp * sin(rad(v->ang))); //translation with distace of opposite
    visualize_maps(v, &i, &j);
    // printf("1- v->ang %f (Vdelta = %f, Hdelta = %f)  (smal_steps = %f) i == %d, j == %d iq = %d iqzab %d\n",v->ang,v->Vdelta,v->Hdelta, smal_steps,i,j,iq,iq);
    // printf("(i = %d iz = %f, j = %d) \n",i, (v->y / v->scal), j);
    v->big_stp = v->big_sidstp;
    iq = 1;
    while (v->big_sidstp < v->smal_stp && (int)v->map[j][i] != '1')
    {
        // printf("(big_step = %f) (i = %d, j = %d) (x/s = %f, y/s = %f) iq = %d (x = %f, y = %f) \n",v->big_stp,i,j,v->x1 / v->scal, v->y1 / v->scal,iq, v->x1, v->y1);
        v->big_stp = (iq * fmax(v->Hdelta, v->Vdelta) + v->big_sidstp);
        v->x1 = v->x + (v->big_stp * cos(rad(v->ang))); //translation with distace of adjacent
        v->y1 = v->y + (v->big_stp * sin(rad(v->ang))); //translation with distace of opposite
        visualize_maps(v, &i, &j);
        iq++;
        // printf("(big_step = %f) (i = %d, j = %d) (x/s = %f, y/s = %f) iq = %d (x = %f, y = %f) \n",v->big_stp,i,j,v->x1 / v->scal, v->y1 / v->scal,iq, v->x1, v->y1);
        if (v->big_stp > v->smal_stp || (int)v->map[j][i] == '1')
            break;
    }
}
// TODO puts cos and sin in var
void horisontal_intersections(t_data *v)
{
    // printf(" cos = %f sin = %f\n",   3 * cos(rad(v->orientation)),  3 * sin(rad(v->orientation)));
    printf("(DVside = %f, DHside = %f)\n",v->DVside,v->DHside);
    printf("(Vdelta = %f, Hdelta = %f)\n",v->Vdelta,v->Hdelta);
    inc_smal_steps(v);
    inc_big_steps(v);
    // printf("big %f small %f\n", v->big_stp, v->smal_stp);
    v->x1 = v->x + (fmin(v->smal_stp, v->big_stp) * cos(rad(v->ang))) ; //translation with distace of adjacent
    v->y1 = v->y + (fmin(v->smal_stp, v->big_stp) * sin(rad(v->ang))) ; //translation with distace of opposite
}