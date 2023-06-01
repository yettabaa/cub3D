/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:39:14 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/01 02:06:49 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	dda(t_data *v, double x0, double y0, double x1, double y1, int color)
{
	int		i;
	double	xinc;
	double	yinc;
	double	steps;

	steps = fmax(fabs(x0 - x1), fabs(y0 - y1));
	xinc = (x1 - x0) / steps;
	yinc = (y1 - y0) / steps;
	i = 0;
	while (i <= steps)
	{
		if (round(x0) >= 0 && round(x0) < WIDTH && round(y0) >= 0 && round(y0) < HIGHT)
			my_mlx_pixel_put(v ,round(x0), round(y0), color);
		x0 = x0 + xinc;
		y0 = y0 + yinc;
		i++;
	}
}

void rectangle(t_data *v, int x, int y, int color)
{
    int i;
    int j;

    j = -1;
    while (++j < v->scal)
    {
        i = -1;
        while (++i < v->scal)
            my_mlx_pixel_put(v, x + i, y + j, color);
    }
}

void disc(t_data *v, int color)
{
    double x0;
    double y0;
    double radius;

    radius = v->scal / 100;
    y0 = -radius;
    while (y0 <= radius)
    {
        x0 = -radius;
        while (x0 <= radius)
        {
            if (x0 * x0 + y0 * y0 <= radius * radius)
                my_mlx_pixel_put(v, x0 + v->x, y0 + v->y, color);
            x0++;
        }
        y0++;
    }
}