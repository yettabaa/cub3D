/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:52:33 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/13 00:30:49 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int is(t_data *v, int flag)
{
    int ang_nor;
    
    ang_nor = normalize_angle_360(v->ryc.ang);
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

double	rad(double angle)
{
	return (angle * (M_PI / 180));
}

double normalize_angle_360(double x)
{
    x = fmod(x,360);
    if (x < 0)
        x += 360;
    return x;
}

void	ft_error(const char *str)
{
	perror(str);
	exit(1);
}