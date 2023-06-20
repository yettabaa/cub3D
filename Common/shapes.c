/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 00:52:24 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/20 04:50:26 by yettabaa         ###   ########.fr       */
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


void	old_dda(t_data *v, double x0, double y0, unsigned int color)// hyedha
{
	int		i;
	double	xinc;
	double	yinc;
	double	steps;

	steps = fmax(fabs(x0 - v->xw), fabs(y0 - v->yw));
	xinc = (v->xw - x0) / steps;
	yinc = (v->yw - y0) / steps;
	i = 0;
	while (i <= steps + v->epsilon)
	{
		if (round(x0) >= 0 && round(x0) < WIDTH && round(y0) >= 0 && round(y0) < HIGHT)
			my_mlx_pixel_put(v ,round(x0), round(y0), color);
		x0 = x0 + xinc;
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

void disc(t_data *v, double x, double y, int color, double radius)
{
    double x0;
    double y0;
    // double radius;

    // radius = v->scal / 3;
    y0 = -radius;
    while (y0 <= radius)
    {
        x0 = -radius;
        while (x0 <= radius)
        {
			if (round(x0 + x) >= 0 && round(x0 + x) < WIDTH && round(y0 + y) >= 0 && round(y0 + y) < HIGHT)
            	if ((x0 * x0) + y0 * y0 <= radius * radius)
                	my_mlx_pixel_put(v, x0 + x, y0 + y, color);
            x0++;
        }
        y0++;
    }
}

double des_betw_2pt(double x0, double y0, double x1, double y1)
{
    return(sqrt(pow(fabs(x0 - x1), 2) + pow(fabs(y0 - y1), 2)));
}

void	ft_error(const char *str)
{
	perror(str);
	exit(1);
}
