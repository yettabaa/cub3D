/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvements.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 01:55:51 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/01 04:13:13 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void direction(t_data *v, int param)
{
    int i;
    int j;
    int inc;
    double dir;
    
    inc = 5; // scal / 8
    dir = v->orientation;
    (param == S) && (dir = v->orientation - 180);
    (param == A) && (dir = v->orientation - 90);
    (param == D) && (dir = v->orientation + 90);
    i = (inc * cos(rad(dir)) + v->x) / v->scal;
    j = (inc * sin(rad(dir)) + v->y) / v->scal;
    while (inc-- > 0 && (int)v->map[j][i] == '1')
    {
        i = (inc * cos(rad(dir)) + v->x) / v->scal; 
        j = (inc * sin(rad(dir)) + v->y) / v->scal;
    }
    v->x += (inc - 1) * cos(rad(dir));
    v->y += (inc - 1) * sin(rad(dir));
}
