/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 03:22:31 by yettabaa          #+#    #+#             */
/*   Updated: 2023/05/27 20:02:55 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void visualize_maps(t_data *v, int *i, int *j, int flage)
{
    *j = (v->y1 + v->error) / v->scal;
    *i = (v->x1 + v->error) / v->scal;
    if (flage == SMALL)
    {
        if (*i && is(v, LEFT) && v->Vdelta < v->Hdelta)
            *i -= 1;
        if(*j && is(v, UP) && v->Vdelta > v->Hdelta) 
            *j -= 1;
    }
    else
    {
        if (*i &&  is(v, LEFT) && v->Vdelta > v->Hdelta)
            *i -= 1;
        if(*j && is(v, UP) && v->Vdelta < v->Hdelta) 
            *j -= 1;
    }
}

void inc_smal_steps(t_data *v)
{
    int i;
    int j;
    int iq;

    // puts("----------------");
    if (v->Vdelta < v->Hdelta)
        v->smal_sidstp = v->DVside;
    else
        v->smal_sidstp = v->DHside;
    printf("(x_p = %f ,y_p = %f) (x_ry = %f, y_ry = %f) DVside = %f DHside %f\n",v->x, v->y, v->x1, v->y1,v->DVside, v->DHside);
    v->x1 = v->x + (v->smal_sidstp * cos(rad(v->ang))); // (1,5) angle 225
    v->y1 = v->y + (v->smal_sidstp * sin(rad(v->ang)));
    visualize_maps(v, &i, &j, SMALL);
    // j = (v->y1 + v->error) / v->scal;
    // i = (v->x1 + v->error) / v->scal;
    // if (i && v->ang > 90 && v->ang < 270 && v->DVside < v->DHside) // i  > 0 handline cos NULL
    // {
    //     puts("i--");
    //     i -= 1;
    // }
    // if(j && v->ang > 180 && v->ang < 360 && v->DVside > v->DHside) 
    //     j -= 1;
    printf("(i = %d iz = %f, j = %d) \n",i, (v->y / v->scal), j);
    v->smal_stp = v->smal_sidstp;
    if ((int)v->map[j][i] == '1' && (int)v->map[(int)((v->y - v->error)  / v->scal)][(int)((v->x - v->error) / v->scal)] == '1') 
    {
        v->x1 = v->x;
        v->y1 = v->y;
        return ;
    }
    iq = 1;
    // printf("v->ang = %f v->Smal_sidstp %f  (x = %f, y = %f) (i = %d, j = %d)\n",v->ang, v->smal_sidstp,v->x1,v->y1,i,j);
    while ((int)v->map[j][i] != '1')
    {
        v->smal_stp = (iq * fmin(v->Hdelta, v->Vdelta) + v->smal_sidstp);
        v->x1 = v->x + (v->smal_stp * cos(rad(v->ang))); //translation with distace of adjacent
        v->y1 = v->y + (v->smal_stp * sin(rad(v->ang))); //translation with distace of opposite
        visualize_maps(v, &i, &j, SMALL);
        // printf("v->ang %f (Vdelta = %f, Hdelta = %f)  (smal_steps = %f) i == %d, j == %d iq = %d (x = %f, y = %f) \n",v->ang,v->Vdelta,v->Hdelta, v->smal_stp,i,j,iq, v->x1, v->y1);
        iq++;
    }
    
}

void inc_big_steps(t_data *v)
{
    int i;
    int j;
    int iq;
    
    if (v->Vdelta < v->Hdelta)
        v->big_sidstp = v->DHside;
    else
        v->big_sidstp = v->DVside;
    v->x1 = v->x + (v->big_sidstp * cos(rad(v->ang))); //translation with distace of adjacent
    v->y1 = v->y + (v->big_sidstp * sin(rad(v->ang))); //translation with distace of opposite
    visualize_maps(v, &i, &j, BIG);
    // j = (v->y1 + v->error) / v->scal;
    // i = (v->x1 + v->error) / v->scal;
    // if (v->ang > 90 && v->ang < 270 && v->Vdelta > v->Hdelta)
    //     i -= 1;
    // if(v->ang > 180 && v->ang < 360 && v->Vdelta < v->Hdelta) 
    //     j -= 1;
    // printf("1- v->ang %f (Vdelta = %f, Hdelta = %f)  (smal_steps = %f) i == %d, j == %d iq = %d iqzab %d\n",v->ang,v->Vdelta,v->Hdelta, smal_steps,i,j,iq,iq);
    iq = 1;
    v->big_stp = v->big_sidstp;
    while (v->big_sidstp < v->smal_stp && (int)v->map[j][i] != '1')
    {
        v->big_stp = (iq * fmax(v->Hdelta, v->Vdelta) + v->big_sidstp);
        v->x1 = v->x + (v->big_stp * cos(rad(v->ang))); //translation with distace of adjacent
        v->y1 = v->y + (v->big_stp * sin(rad(v->ang))); //translation with distace of opposite
        visualize_maps(v, &i, &j, BIG);
        iq++;
        // printf("v->ang %f (Vdelta = %f, Hdelta = %f)  (smal_steps = %f) i == %d, j == %d iq = %d (x = %f, y = %f) \n",v->ang,v->Vdelta,v->Hdelta, v->smal_stp,i,j,iq, v->x1, v->y1);
        // printf("2-v->ang %f (Vdelta = %f, Hdelta = %f)  (smal_steps = %f, big_steps = %f) i == %d, j == %d iq = %d iqzab %d\n",v->ang,v->Vdelta,v->Hdelta, smal_steps, big_steps,i,j,iq,iqtale3);
        if (v->big_stp > v->smal_stp || (int)v->map[j][i] == '1')
            break;
    }
}

void horisontal_intersections(t_data *v)
{
    inc_smal_steps(v);
    // inc_big_steps(v);
    // v->x1 = v->x + (fmin(v->smal_stp, v->big_stp) * cos(rad(v->ang))) + v->error; //translation with distace of adjacent
    // v->y1 = v->y + (fmin(v->smal_stp, v->big_stp) * sin(rad(v->ang))) + v->error; //translation with distace of opposite
}