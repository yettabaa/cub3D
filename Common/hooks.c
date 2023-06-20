/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 00:57:13 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/20 04:10:59 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	update(t_data *v)
{
	int	walk_step;

	v->orientation += v->hook.angle_dir * v->hook.angle_speed;
	walk_step = v->hook.walk_dir * v->hook.walk_speed;
	if (raycasting(v, v->orientation + v->hook.angleOr) <= 2)
		return ;
	v->x += walk_step * cos(Rad(v->orientation + v->hook.angleOr));
	v->y += walk_step * sin(Rad(v->orientation + v->hook.angleOr));
}

int	destroy(void)
{
	exit(0);
	return (0);
}

int	key_press(int keycode, t_data *v)
{
	(keycode == 123) && (v->hook.angle_dir = -1);
	(keycode == 124) && (v->hook.angle_dir = 1);
	(keycode == 125) && (v->hook.angle_dir = -0.1);
	(keycode == 126) && (v->hook.angle_dir = 0.1);
	(keycode == W) && (v->hook.walk_dir = 1);
	if (keycode == 53)
		exit(0);
	else if (keycode == S)
	{
		v->hook.walk_dir = 1;
		v->hook.angleOr = -180;
	}
	else if (keycode == A)
	{
		v->hook.walk_dir = 1;
		v->hook.angleOr = -90;
	}
	else if (keycode == D)
	{
		v->hook.walk_dir = 1;
		v->hook.angleOr = 90;
	}
	// mlx_destroy_image(v->mlx.mlx, v->mlx.img);
	// v->mlx.img = mlx_new_image(v->mlx.mlx, WIDTH, HIGHT);
	// v->mlx.addr = mlx_get_data_addr(v->mlx.img, &v->mlx.bits_per_pixel,
			//&v->mlx.line_length,
	// 		&v->mlx.endian);
	// cube3D_bonus(v);
	// mlx_put_image_to_window(v->mlx.mlx, v->mlx.mlx_win, v->mlx.img, 0, 0);
	return (0);
}

int	key_release(int keycode, t_data *v)
{
	(keycode == 123) && (v->hook.angle_dir = 0);
	(keycode == 124) && (v->hook.angle_dir = 0);
	(keycode == 125) && (v->hook.angle_dir = 0);
	(keycode == 126) && (v->hook.angle_dir = 0);
	(keycode == W) && (v->hook.walk_dir = 0);
	if (keycode == S)
	{
		v->hook.walk_dir = 0;
		v->hook.angleOr = 0;
	}
	else if (keycode == A)
	{
		v->hook.walk_dir = 0;
		v->hook.angleOr = 0;
	}
	else if (keycode == D)
	{
		v->hook.walk_dir = 0;
		v->hook.angleOr = 0;
	}
	return (0);
}

int	mouse_hook(int x, int y, t_data *v)
{
	int width_half = WIDTH / 2;
	if (y > 0 && y < HIGHT && x < WIDTH && x > width_half + 100)
		v->hook.angle_dir = +0.5;
	else if (y > 0 && y < HIGHT && x < WIDTH && x > 0 && x < width_half - 100)
		v->hook.angle_dir = -0.5;
	else
		v->hook.angle_dir = 0;
	return (0);
}