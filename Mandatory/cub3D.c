/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:39:19 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/16 20:00:14 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void initialisation(t_data *v)
{
    v->epsilon = 1e-8; // ??? hit the wall in the origin axis  // (1,5) angle 225
    v->scal = 12; // 19
    v->orientation = strchr_c("WSEN", v->pars.palayer_dir) * 90;
    // v->orientation = 90;
    v->hook.angle_dir = 0;
    v->hook.angle_speed = 3;
    v->hook.walk_dir = 0;
    v->hook.walk_speed = 1;
    v->hook.angleOr = 0;
    v->x = (v->pars.x * v->scal + v->scal / 2);
    v->y = (v->pars.y * v->scal + v->scal / 2);
    get_textures(v);
}

void cube3D(t_data *v)
{
    double vi;
    double frequency;
    
    v->x_wind = 0;
    vi = 0;
    frequency = 60;
    update(v);
    while (vi <= (frequency + v->epsilon))
    {
        // puts("---------------------------------\n");
        v->ryc.ang = normalize_angle_360(v->orientation -30 + vi);
        raycasting(v, v->ryc.ang, '1');
        rendering_wall(v, v->ryc.ang);
        vi += (double)60 / (double)WIDTH;
        v->x_wind += 1;
    }
}

int loop_hook(void *ptr)
{
    t_data *v;
    
    v = ptr;
	v->mlx.img = mlx_new_image(v->mlx.mlx, WIDTH, HIGHT);
	v->mlx.addr = mlx_get_data_addr(v->mlx.img, &v->mlx.bits_per_pixel, &v->mlx.line_length,
			&v->mlx.endian);
	cube3D(v);
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
    if_map_is_valid(ac, av, &v.pars); // rename //parsing
    initialisation(&v);
    cube3D(&v);
	mlx_put_image_to_window(v.mlx.mlx, v.mlx.mlx_win, v.mlx.img, 0, 0);
    mlx_loop_hook(v.mlx.mlx, loop_hook, &v);
    mlx_hook(v.mlx.mlx_win, 2, 0, key_press, &v);
    mlx_hook(v.mlx.mlx_win, 3, 0, key_release, &v);
    mlx_hook(v.mlx.mlx_win, 17, 0, destroy, &v);
	mlx_loop(v.mlx.mlx);
}

// int main()
// {
//     int h;
//     int w;
//     int bitp;
//     int line;
//     int end;
//     void *mlx = mlx_init();
//     void *img =  mlx_xpm_file_to_image(mlx, "/Users/yettabaa/Desktop/cub3D/textures/door/door_44.xpm", &w, &h);

//     unsigned int *no_buff = (unsigned int *)mlx_get_data_addr(img, &bitp, &line, &end);
//     // str = malloc(10);
//     printf("line = %d\n", line);
//     int x = 10;
//     int y = 10;
//     int i = y * 64 + x;
//     // unsigned int c = no_buff[i + 0] << 16 | no_buff[i + 1] << 8 | no_buff[i + 2] | no_buff[i + 3] << 24;
//     unsigned int c = no_buff[i];
    
//     printf("%u\n", c >> 24 & 0x000000ff);
//     printf("%u\n", c);
    
// }