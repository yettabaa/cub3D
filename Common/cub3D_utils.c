/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 00:57:49 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/20 04:06:58 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int is(t_data *v, double ang, int flag)
{
    int ang_nor;
    (void)v;
    
    ang_nor = normalize_angle_360(ang);
    if (flag == LEFT && ang_nor >= 90 && ang_nor < 270)
        return (1);
    if (flag == RIGHT && !(ang_nor >= 90 && ang_nor < 270))
        return (1);
    else if (flag == UP && ang_nor > 180 && ang_nor < 360)
        return (1);
    else if (flag == DOWN && ang_nor >= 0 && ang_nor < 180)
        return (1);
    else
        return(0);    
}

double	Rad(double angle)
{
	return (angle * (M_PI / 180));
}

double Deg(double radians) 
{
    return radians * (180.0 / M_PI);
}

double normalize_angle_360(double x)
{
    x = fmod(x,360);
    if (x < 0)
        x += 360;
    return x;
}


int check_(t_data *v, int i, int j, int flag)
{
    if (flag == WALL && i >= 0 && i < v->pars.i && j >= 0 && j < v->pars.j && (int)v->pars.map2[j][i] != '1' && (int)v->pars.map2[j][i] != 32)
        return(1);
    if (flag == DOOR && i >= 0 && i < v->pars.i && j >= 0 && j < v->pars.j && (int)v->pars.map2[j][i] == '2')
        return(1);
    if(flag == 0 && i >= 0 && i < v->pars.i && j >= 0 && j < v->pars.j && (int)v->pars.map2[j][i] == '1')
        return(1);
    return(0);    
}