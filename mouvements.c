/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvements.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 01:55:51 by yettabaa          #+#    #+#             */
/*   Updated: 2023/05/31 03:47:38 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void ft_forward(t_data *v)
{
    int inc = 10;
    int i;
    int j;
    
    i = (inc * cos(rad(v->orientation)) + v->x) / v->scal; 
    j = (inc * sin(rad(v->orientation)) + v->y) / v->scal;
    // printf("i = %d, j = %d\n", i, j);
    // printf("map = %d\n", (int)v->map[i][j]);
    // printf("map = %d\n", (int)v->map[j][i]);
    // printf("%d\n", (inc >= 0 && (int)v->map[j][i] == 1));
    while (inc >= 1 && (int)v->map[j][i] == '1')
    {
        // puts("ss");
        // printf("inc = %d i = %d, j = %d\n",inc, i, j);
        inc--;
        i = (inc * cos(rad(v->orientation)) + v->x) / v->scal; 
        j = (inc * sin(rad(v->orientation)) + v->y) / v->scal;
        // if ((int)v->map[j][i] == '1')
        //     break;
    }
    v->x += inc * cos(rad(v->orientation));
    v->y += inc * sin(rad(v->orientation));
}