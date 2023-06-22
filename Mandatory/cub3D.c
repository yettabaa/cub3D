/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:39:19 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/22 05:56:07 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void initialisation(t_data *v)
{
    v->epsil = 1e-8; // ??? hit the wall in the origin axis  // (1,5) angle 225
    v->scal = 12; // 19
    v->orientation = strchr_c("WSEN", v->pars.palayer_dir) * 90;
    v->hook.angle_dir = 0;
    v->hook.angle_speed = 3;
    v->hook.walk_dir = 0;
    v->hook.walk_speed = 1.5;
    v->hook.angleor = 0;
    v->x = (v->pars.x * v->scal + v->scal / 2);
    v->y = (v->pars.y * v->scal + v->scal / 2);
    v->sprite = NULL;
    v->door.door_buff = NULL;
	v->sprt.sprite_buff = NULL;
    get_textures(v);
}
void maps2d(t_data *v)
{
    int i;
    int j;
    
    j = 0;
    while ((int)v->pars.map2[(int)(j / v->scal)])
    {
        i = 0;
        while ((int)v->pars.map2[(int)(j / v->scal)][(int)(i / v->scal)])
        {
                if ((int)v->pars.map2[(int)(j / v->scal)][(int)(i / v->scal)] == '1')
                    my_pixel_put(v, i, j, 0);
                else if ((int)v->pars.map2[(int)(j / v->scal)][(int)(i / v->scal)] == '2')
                    my_pixel_put(v, i, j, 0xff);
                else if ((int)v->pars.map2[(int)(j / v->scal)][(int)(i / v->scal)] != 32)
                    my_pixel_put(v, i, j, 0xffffff); 
            i++;
        }
        j++;
    }
}
void	old_dda(t_data *v, double x0, double y0, unsigned int color) // hyedha
{
	int i;
	double xinc;
	double yinc;
	double steps;

	steps = fmax(fabs(x0 - v->xw), fabs(y0 - v->yw));
	xinc = (v->xw - x0) / steps;
	yinc = (v->yw - y0) / steps;
	i = 0;
	while (i <= steps + v->epsil)
	{
		my_pixel_put(v, round(x0), round(y0), color);
		x0 = x0 + xinc;
		y0 = y0 + yinc;
		i++;
	}
}
void minimaps(t_data *v, int color)
{
    double vi;
    double frequency;
    
    maps2d(v);
    frequency = 60;
    vi = 0;
    while (vi <= (frequency + v->epsil))
    {
        // puts("---------------------------------\n");
        v->ryc.ang = normalize_angle_360(v->orientation -30 + vi);
        raycasting(v, v->ryc.ang);
    
        old_dda(v, v->x , v->y , color);  // round to int for handle the corner in 2d
        vi += 0.1;
    }
}
void cube3D(t_data *v)
{
    double vi;
    double frequency;
    
    v->x_wind = 0;
    vi = 0;
    frequency = 60;
    update(v);
    while (vi <= (frequency + v->epsil))
    {
        // puts("---------------------------------\n");
        v->ryc.ang = normalize_angle_360(v->orientation -30 + vi);
        raycasting(v, v->ryc.ang);
        rendering_wall(v, v->ryc.ang);
        vi += (double)60 / (double)WIDTH;
        v->x_wind += 1;
    }
    minimaps(v, 0x808080);
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
void f()
{
	system("leaks cub3D");
}
int main(int ac ,char **av)
{
	t_data v;

    // atexit(f);
	v.mlx.mlx = mlx_init();
	v.mlx.mlx_win = mlx_new_window(v.mlx.mlx, WIDTH, HIGHT, "cub3D");
	v.mlx.img = mlx_new_image(v.mlx.mlx, WIDTH, HIGHT);
	v.mlx.addr = mlx_get_data_addr(v.mlx.img, &v.mlx.bits_per_pixel, &v.mlx.line_length,
								&v.mlx.endian); 
    parsing(&v, ac, av);
    initialisation(&v);
    cube3D(&v);
	mlx_put_image_to_window(v.mlx.mlx, v.mlx.mlx_win, v.mlx.img, 0, 0);
    mlx_loop_hook(v.mlx.mlx, loop_hook, &v);
    mlx_hook(v.mlx.mlx_win, 2, 0, key_press, &v);
    mlx_hook(v.mlx.mlx_win, 3, 0, key_release, &v);
    mlx_hook(v.mlx.mlx_win, 17, 0, destroy, &v);
	mlx_loop(v.mlx.mlx);
}
// int	main(int ac, char **av)
// {
// 	t_data v;
// 	atexit(f);
// 	parsing(&v, ac, av);
//     initialisation(&v);
// 		// checker_bonus(&v);
// 	int i = 0;
// 	 while (v.pars.map2[i])
//     {
//         printf("|%s|\n", v.pars.map2[i++]);
//     }
// 	free_array(v.pars.map2);
// 	// free_array(v.pars.map);
// 	free(v.pars.so);
// 	free(v.pars.no);
// 	free(v.pars.ea);
// 	free(v.pars.we);
// 	free(v.sprite);
//     printf("i = %d j = %d\n", v.pars.i, v.pars.j);
// }