/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 00:26:29 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/14 05:14:12 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void init_bonus(t_data *v)
{
    v->epsilon = 1e-8; // ??? hit the wall in the origin axis  // (1,5) angle 225
    // v->epsilon = 0.01; // ??? hit the wall in the origin axis  // (1,5) angle 225
    v->scal = 8; // 19
    v->orientation = 90;
    v->hook.angle_dir = 0;
    v->hook.angle_speed = 3;
    v->hook.walk_dir = 0;
    v->hook.walk_speed = 1;
    v->hook.angleOr = 0;
    v->x = (4 * v->scal + v->scal / 2);
    v->y = (1 * v->scal + v->scal / 2);
    get_textures(v);
    get_text_door(v);
    v->door = NULL;
    v->x0_door = 0;
}

void cube3D_bonus(t_data *v)
{
    double vi;
    double frequency;
    
    v->x0 = 0;
    vi = 0;
    frequency = 60;
    update(v);
    while (vi <= (frequency + v->epsilon))
    {
        // puts("---------------------------------\n");
        v->ryc.ang = normalize_angle_360(v->orientation -30 + vi);
        raycasting_bonus(v);
        render_wall_bonus(v);
        vi += (double)60 / (double)WIDTH;
        v->x0 += 1;
    }
    mini_maps(v, 0xff);
}

int loop_hook_bonus(void *ptr)
{
    t_data *v;
    
    v = ptr;
	v->mlx.img = mlx_new_image(v->mlx.mlx, WIDTH, HIGHT);
	v->mlx.addr = mlx_get_data_addr(v->mlx.img, &v->mlx.bits_per_pixel, &v->mlx.line_length,
			&v->mlx.endian);
	cube3D_bonus(v);
	mlx_put_image_to_window(v->mlx.mlx, v->mlx.mlx_win, v->mlx.img, 0, 0);
    mlx_destroy_image(v->mlx.mlx, v->mlx.img);
    return (0);
}

int main(int ac ,char **av)
{
	t_data v;

	v.mlx.mlx = mlx_init();
	v.mlx.mlx_win = mlx_new_window(v.mlx.mlx, WIDTH, HIGHT, "Hello world!");
	v.mlx.img = mlx_new_image(v.mlx.mlx, WIDTH, HIGHT);
	v.mlx.addr = mlx_get_data_addr(v.mlx.img, &v.mlx.bits_per_pixel, &v.mlx.line_length,
								&v.mlx.endian); 
    if_map_is_valid(ac, av, &v.pars); // rename
    init_bonus(&v);
    cube3D_bonus(&v);
	mlx_put_image_to_window(v.mlx.mlx, v.mlx.mlx_win, v.mlx.img, 0, 0);
    mlx_loop_hook(v.mlx.mlx, loop_hook_bonus, &v);
    mlx_hook(v.mlx.mlx_win, 2, 0, key_press, &v);
    mlx_hook(v.mlx.mlx_win, 3, 0, key_release, &v);
    mlx_hook(v.mlx.mlx_win, 17, 0, destroy, &v);
	mlx_loop(v.mlx.mlx);
}