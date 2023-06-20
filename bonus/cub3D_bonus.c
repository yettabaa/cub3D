/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 00:26:29 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/20 04:04:53 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_bonus(t_data *v)
{
	v->epsilon = 1e-8; // ??? hit the wall in the origin axis 
		// (1,5) angle 225
	v->scal = 12;      // 19
	v->orientation = strchr_c("WSEN", v->pars.palayer_dir) * 90;
	// v->orientation = 0;
	v->hook.angle_dir = 0;
	v->hook.angle_speed = 4;
	v->hook.walk_dir = 0;
	v->hook.walk_speed = 2;
	v->hook.angleOr = 0;
	v->ProjPlane = (WIDTH / 2) / tan(Rad(30));
	v->x = (v->pars.x * v->scal + v->scal / 2);
	v->y = (v->pars.y * v->scal + v->scal / 2);
	v->sprt.frames = 0;
	v->sprt.ind_sprite_text = 0;
	get_textures(v);
	get_text_door(v);
	get_text_sprites(v);
	v->object = NULL;
	v->MiniMap.raduis = HIGHT / 10;
	v->MiniMap.trans_x = (WIDTH / 2) - v->x - 650;
    v->MiniMap.trans_y = v->MiniMap.raduis - v->y + 750;
}


void	cube3D_bonus(t_data *v)
{
	t_object *hold;
	double	vi;
	double	frequency;

	v->x_wind = 0;
	vi = 0;
	frequency = 60;
	// puts("---------------------------------\n");
	update(v);
	hold = visible_sprite(v);
	while (vi < frequency)
	{
		v->object = copie_list(hold);
		v->ryc.ang = normalize_angle_360(v->orientation - 30 + vi);
		raycasting_bonus(v, v->ryc.ang);
		render_wall_bonus(v, v->ryc.ang);
		vi += (double)60 / (double)WIDTH;
		v->x_wind += 1;
	}
	mini_maps(v, 0x808080);
	render_sprite_MiniMap(v, hold);
}

int	loop_hook_bonus(void *ptr)
{
	t_data	*v;

	v = ptr;
	v->mlx.img = mlx_new_image(v->mlx.mlx, WIDTH, HIGHT);
	v->mlx.addr = mlx_get_data_addr(v->mlx.img, &v->mlx.bits_per_pixel,
			&v->mlx.line_length, &v->mlx.endian);
	cube3D_bonus(v);
	mlx_put_image_to_window(v->mlx.mlx, v->mlx.mlx_win, v->mlx.img, 0, 0);
	mlx_destroy_image(v->mlx.mlx, v->mlx.img);
	return (0);
}

int	main(int ac, char **av)
{
	t_data v;

	v.mlx.mlx = mlx_init();
	v.mlx.mlx_win = mlx_new_window(v.mlx.mlx, WIDTH, HIGHT, "Hello world!");
	v.mlx.img = mlx_new_image(v.mlx.mlx, WIDTH, HIGHT);
	v.mlx.addr = mlx_get_data_addr(v.mlx.img, &v.mlx.bits_per_pixel,
			&v.mlx.line_length, &v.mlx.endian);
	parsing_bonus(&v, ac, av); // rename// parsing bonus
	   int i = 0;
    while (v.pars.map2[i])
    {
        printf("|%s|\n", v.pars.map2[i++]);
    }
    printf("i = %d j = %d\n", v.pars.i, v.pars.j);
	init_bonus(&v);
	checker_bonus(&v); // checker bonus
	// if (v.sprite)
	//     printf("x = %f y = %f\n",  v.sprite[0].xs,  v.sprite[0].ys);
	cube3D_bonus(&v);
	mlx_put_image_to_window(v.mlx.mlx, v.mlx.mlx_win, v.mlx.img, 0, 0);
	mlx_loop_hook(v.mlx.mlx, loop_hook_bonus, &v);
	mlx_hook(v.mlx.mlx_win, 6, 0, mouse_hook, &v);
	mlx_hook(v.mlx.mlx_win, 2, 0, key_press, &v);
	mlx_hook(v.mlx.mlx_win, 3, 0, key_release, &v);
	mlx_hook(v.mlx.mlx_win, 17, 0, destroy, &v);
	mlx_loop(v.mlx.mlx);
}