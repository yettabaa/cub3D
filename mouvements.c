/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvements.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 01:55:51 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/05 02:56:42 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// void direction(t_data *v, int param)
// {
//     int i;
//     int j;
//     int inc;
//     double dir;
    
//     inc = 4; // scal / 8
//     dir = v->orientation;
//     (param == S) && (dir = v->orientation - 180);
//     (param == A) && (dir = v->orientation - 90);
//     (param == D) && (dir = v->orientation + 90);
//     i = (inc * cos(rad(dir)) + v->x) / v->scal;
//     j = (inc * sin(rad(dir)) + v->y) / v->scal;
//     while (inc-- > 1 && (int)v->map[j][i] == '1')
//     {
//         i = (inc * cos(rad(dir)) + v->x) / v->scal; 
//         j = (inc * sin(rad(dir)) + v->y) / v->scal;
//     }
//     v->x += (inc - 1) * cos(rad(dir));
//     v->y += (inc - 1) * sin(rad(dir));
// }
void direction(t_data *v, int param)
{
    int i;
    int j;
    int inc;
    int steps;
    double dir;
    
    steps = 1;
    inc = 4; // scal / 8
    dir = v->orientation;
    (param == S) && (dir = v->orientation - 180);
    (param == A) && (dir = v->orientation - 90);
    (param == D) && (dir = v->orientation + 90);
    i = (steps * cos(rad(dir)) + v->x) / v->scal;
    j = (steps * sin(rad(dir)) + v->y) / v->scal;
    // puts("----");
    while (inc > steps && (int)v->map[j][i] != '1')
    {
        steps++;
        i = (steps * cos(rad(dir)) + v->x) / v->scal; 
        j = (steps * sin(rad(dir)) + v->y) / v->scal;
        // printf("%d\n", steps);
    }
    if ((int)v->map[j][i] == '1')
        return ;
    if (steps != inc)
    {
        v->x += (steps - 4) * cos(rad(dir));
        v->y += (steps - 4) * sin(rad(dir));
    }
    else
    {
        v->x += (steps) * cos(rad(dir));
        v->y += (steps) * sin(rad(dir));
    }
}

void update(t_data *v)
{
    int walk_step;
    int i;
    int j;
    
    v->orientation += v->angle_dir * v->angle_speed;
    walk_step = v->walk_dir * v->walk_speed;
    i = (v->x + (v->walk_dir * (v->walk_speed + 1)) * cos(rad(v->orientation))) / v->scal;
    j = (v->y + (v->walk_dir * (v->walk_speed + 1)) * sin(rad(v->orientation))) / v->scal;
    if ((int)v->map[j][i] == '1')
        return ;
    v->x += walk_step * cos(rad(v->orientation));
    v->y += walk_step * sin(rad(v->orientation));
}
