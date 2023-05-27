/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:52:33 by yettabaa          #+#    #+#             */
/*   Updated: 2023/05/27 19:02:05 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int is(t_data *v, int flag)
{
    if (flag == LEFT && v->ang > 90 && v->ang < 270)
        return (1);
    if (flag == RIGHT && !(v->ang > 90 && v->ang < 270))
        return (1);
    else if (flag == UP && v->ang > 180 && v->ang < 360)
        return (1);
    else if (flag == DOWN && v->ang > 0 && v->ang < 0)
        return (1);
    else
        return(0);    
}

t_rad	rad(t_deg angle)
{
	return (angle * (M_PI / 180));
}

double normalize_angle_180(double x)
{
    // int tmp = x;

    // if (x <= 180)
    //     return x;
    // x = fmod(x + 180,360);
    // if (x < 0)
    //     x += 360;
    // (tmp > 180) && (x *= -1);    
    // return x ;
    if (x <= 180)
        return x;    
    return x -360 ;
}

double normalize_angle_360(double x)
{
    x = fmod(x,360);
    if (x < 0)
        x += 360;
    return x;
}