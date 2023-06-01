/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvements.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 01:55:51 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/01 02:20:34 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void go_forward(t_data *v)
{
    int inc = 5;
    // int inct = 20;
    int i;
    int j;
    
    i = (inc * cos(rad(v->orientation)) + v->x) / v->scal;
    j = (inc * sin(rad(v->orientation)) + v->y) / v->scal;
    // printf("i = %d, j = %d\n", i, j);
    // printf("map = %d\n", (int)v->map[i][j]);
    // visualize_maps(v, &i, &j, 0);
    while (inc >= 0 && (int)v->map[j][i] == '1')
    {
        // puts("ss");
        inc--;
        // visualize_maps(v, &i, &j, 0);
        i = (inc * cos(rad(v->orientation)) + v->x) / v->scal; 
        j = (inc * sin(rad(v->orientation)) + v->y) / v->scal;
        // printf("inc = %d i = %d, j = %d\n",inc, i, j);
        // if ((int)v->map[j][i] == '1')
        //     break;
    }
    // if ((int)v->map[j][i] == '1')
    //     return ;
    v->x += (inc - 1) * cos(rad(v->orientation));
    v->y += (inc - 1) * sin(rad(v->orientation));
    
    // v->x += (v->inc - v->inct / 3) * cos(rad(v->orientation));
    // v->y += (v->inc - v->inct / 3) * sin(rad(v->orientation));

}
void go_back(t_data *v)
{
    int inc = 5;
    int i;
    int j;
    
    i = (v->x - inc * cos(rad(v->orientation))) / v->scal; 
    j = (v->y - inc * sin(rad(v->orientation))) / v->scal;
    // printf("i = %d, j = %d\n", i, j);
    // printf("map = %d\n", (int)v->map[i][j]);
    // printf("map = %d\n", (int)v->map[j][i]);
    // printf("%d\n", (inc >= 0 && (int)v->map[j][i] == 1));
    // visualize_maps(v, &i, &j, 0);
    while (inc >= 0 && (int)v->map[j][i] == '1')
    {
        // puts("ss");
        inc--;
        
        i = (v->x - inc * cos(rad(v->orientation))) / v->scal; 
        j = (v->y - inc * sin(rad(v->orientation))) / v->scal;

        // printf("inc = %d i = %d, j = %d\n",inc, i, j);
        // if ((int)v->map[j][i] == '1')
        //     break;
    }
    v->x -= (inc - 1) * cos(rad(v->orientation));
    v->y -= (inc - 1) * sin(rad(v->orientation));
}