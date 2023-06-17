/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvements.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 01:55:51 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/16 03:53:42 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void update(t_data *v)
{
    int walk_step;
    
    v->orientation += v->hook.angle_dir * v->hook.angle_speed;
    walk_step = v->hook.walk_dir * v->hook.walk_speed;
    if (raycasting(v, v->orientation + v->hook.angleOr, '1') <= 2)
        return ;
    v->x += walk_step * cos(rad(v->orientation + v->hook.angleOr));
    v->y += walk_step * sin(rad(v->orientation + v->hook.angleOr));
}

int destroy(void)
{
    exit(0);
    return (0);
}

int	key_press(int keycode, t_data *v)
{
    if (keycode == 53)
		exit(0);
    else if (keycode == 123)
		v->hook.angle_dir = -1;
	else if (keycode == 124)
		v->hook.angle_dir = 1;
    else if (keycode == 125)
		v->hook.angle_dir = -0.1;
	else if (keycode == 126)
		v->hook.angle_dir = 0.1;
    else if (keycode == W)
        v->hook.walk_dir = 1;
    else if (keycode == S )
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
	// v->mlx.addr = mlx_get_data_addr(v->mlx.img, &v->mlx.bits_per_pixel, &v->mlx.line_length,
	// 		&v->mlx.endian);
	// cube3D_bonus(v);
	// mlx_put_image_to_window(v->mlx.mlx, v->mlx.mlx_win, v->mlx.img, 0, 0);
    return(0);
}

int key_release(int keycode, t_data *v)
{
    if (keycode == 123)
		v->hook.angle_dir = 0;
	else if (keycode == 124)
		v->hook.angle_dir = 0;
    if (keycode == 125)
		v->hook.angle_dir = 0;
	else if (keycode == 126)
		v->hook.angle_dir = 0;
    else if (keycode == W)
        v->hook.walk_dir = 0;
    else if (keycode == S)
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
    return 0;    
}