/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:39:19 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/07 03:54:31 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void initialisation(t_data *v)
{
    v->epsilon = 1e-8; // ??? hit the wall in the origin axis  // (1,5) angle 225
    // v->epsilon = 0.01; // ??? hit the wall in the origin axis  // (1,5) angle 225
    // v->scal = 69; // 19
    v->scal = 13; // 19
    v->orientation = 0;
    v->hook.angle_dir = 0;
    v->hook.angle_speed = 3;
    v->hook.walk_dir = 0;
    v->hook.walk_speed = 3;
    v->hook.angleOr = 0;
    v->x = (1 * v->scal + v->scal / 2);
    v->y = (5 * v->scal + v->scal / 2);
    fill_textures(v);
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
//     void *img =  mlx_xpm_file_to_image(mlx, "./textures/greystone.xpm", &w, &h);

//     unsigned int *no_buff = (unsigned int *)mlx_get_data_addr(img, &bitp, &line, &end);
//     // str = malloc(10);
//     printf("line = %d\n", line);
//     int x = 3;
//     int y = 4;
//     int i = y * 64 + x;
//     // unsigned int c = no_buff[i + 0] << 16 | no_buff[i + 1] << 8 | no_buff[i + 2] | no_buff[i + 3] << 24;
//     unsigned int c = no_buff[i];
//     printf("%u\n", c);
    
// }