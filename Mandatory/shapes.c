/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:39:14 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/19 05:48:35 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	my_mlx_pixel_put(t_data *v, int x, int y, unsigned int color)
{
	char	*dst;

	dst = v->mlx.addr + (y * v->mlx.line_length + x * (v->mlx.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
	return (1);
}

void	dda_textures(t_data *v, double y0, double y1, int flag)
{
	int		i;
    int x_texel;
    int y_texel;
	double	yinc;
	double	steps;
   
	(flag == CEIL && y1 < 0) && (y1 = 0); // in case if we so cloose of the wall
	(flag == TEXT && y0 < 0) && (y0 = 0);
	(flag == TEXT && y1 > HIGHT) && (y1 = HIGHT);
	(flag == FLOOR && y0 > HIGHT) && (y0 = HIGHT);
	steps = fabs(y0 - y1);
	yinc = (y1 - y0) / steps;
	i = 0;
    (v->txt.hitWall == VER) && (x_texel = v->txt.width * fmod(v->yw , v->scal) / v->scal);
    (v->txt.hitWall == HORI) && (x_texel = v->txt.width * fmod(v->xw , v->scal) / v->scal);
	while (i < steps)
	{
        y_texel = v->txt.height * (i + (fabs(v->y1 - v->y0 - steps) / 2)) / fabs(v->y1 - v->y0);
		if (round(v->x_wind) >= 0 && round(v->x_wind) < WIDTH && round(y0) >= 0 && round(y0) < HIGHT)
		{
			(flag == TEXT) && (my_mlx_pixel_put(v ,round(v->x_wind), round(y0), v->txt.buff[y_texel * (v->txt.line / 4) + x_texel]));
			(flag == CEIL) && (my_mlx_pixel_put(v ,round(v->x_wind), round(y0), v->pars.c));
			(flag == FLOOR) && (my_mlx_pixel_put(v ,round(v->x_wind), round(y0), v->pars.f));
		}
		y0 = y0 + yinc;
		i++;
	}
}

void	dda(t_data *v, double x0, double y0, unsigned int color)
{
	int		i;
	double	xinc;
	double	yinc;
	double	steps;

	steps = fmax(fabs(x0 - v->xw + v->MiniMap.trans_x), fabs(y0 - v->yw + v->MiniMap.trans_y));
	xinc = (v->xw + v->MiniMap.trans_x - x0) / steps;
	yinc = (v->yw + v->MiniMap.trans_y - y0) / steps;
	i = 0;
	while (i <= steps + v->epsilon)
	{
		if (round(x0) >= 0 && round(x0) < WIDTH && round(y0) >= 0 && round(y0) < HIGHT)
			if ((i * xinc) * (i * xinc) + (i * yinc) * (i * yinc) < v->MiniMap.raduis * v->MiniMap.raduis)
				my_mlx_pixel_put(v ,(x0), (y0), color);
		x0 = x0 + xinc;
		y0 = y0 + yinc;
		i++;
	}
}
void	dda_old(t_data *v, double x0, double y0, double x1, double y1, int color)
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
		if (floor(x0) >= 0 && floor(x0) < WIDTH && floor(y0) >= 0 && floor(y0) < HIGHT)
			my_mlx_pixel_put(v ,floor(x0), floor(y0), color);
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
			if ((x + i) >= 0 && (x + i) < WIDTH && (y + j) >= 0 && (y + j) < HIGHT)
        	    	my_mlx_pixel_put(v, x + i, y + j, color);
				// if (((i) * (i)) + ((j ) * (j )) <= 10 * 10)
    }
}

void disc(t_data *v, double x, double y, int color)
{
    double x0;
    double y0;
    double radius;

    radius = v->scal / 3;
    y0 = -radius;
    while (y0 <= radius)
    {
        x0 = -radius;
        while (x0 <= radius)
        {
            if ((x0 * x0) + y0 * y0 <= radius * radius)
                my_mlx_pixel_put(v, x0 + x, y0 + y, color);
            x0++;
        }
        y0++;
    }
}

