/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 00:26:29 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/22 18:41:38 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_bonus(t_data *v)
{
	v->epsil = 1e-8; // ??? hit the wall in the origin axis 
	v->scal = 8;      // 19
	v->orientation = strchr_c("WSEN", v->pars.palayer_dir) * 90;
	v->hook.angle_dir = 0;
	v->hook.angle_speed = 3;
	v->hook.walk_dir = 0;
	v->hook.walk_speed = 1;
	v->hook.angleor = 0;
	v->projplane = (WIDTH / 2) / tan(rad(30));
	v->x = (v->pars.x * v->scal + v->scal / 2);
	v->y = (v->pars.y * v->scal + v->scal / 2);
	v->sprt.frames = 0;
	v->sprt.ind_sprite_text = 0;
	v->sprite = NULL;
	v->door.door_buff = NULL;
	v->sprt.sprite_buff = NULL;
	get_textures(v);
	get_text_door(v);
	get_text_sprites(v);
	v->minimap.raduis = HIGHT / 10;
	v->minimap.trans_x = (WIDTH / 2) - v->x - 650;
    v->minimap.trans_y = v->minimap.raduis - v->y + 750;
}


void	cube3D_bonus(t_data *v)
{
	t_object *hold;
	t_object *object;
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
		object = copie_list(v, hold);
		v->ryc.ang = normalize_angle_360(v->orientation - 30 + vi);
		raycasting_bonus(v,&object, v->ryc.ang);
		render_wall_bonus(v,object, v->ryc.ang);
		clear_objt(&object);
		vi += (double)60 / (double)WIDTH;
		v->x_wind += 1;
	}
	mini_maps(v, 0x808080);
	render_sprite_minimap(v, hold);
	clear_objt(&hold);
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
void f()
{
	system("leaks cub3D_bonus");
}
int	main(int ac, char **av)
{
	t_data v;
	
	// atexit(f);
	v.mlx.mlx = mlx_init();
	v.mlx.mlx_win = mlx_new_window(v.mlx.mlx, WIDTH, HIGHT, "cub3D_bonus");
	v.mlx.img = mlx_new_image(v.mlx.mlx, WIDTH, HIGHT);
	v.mlx.addr = mlx_get_data_addr(v.mlx.img, &v.mlx.bits_per_pixel,
			&v.mlx.line_length, &v.mlx.endian);
	parsing_bonus(&v, ac, av);
	init_bonus(&v);
	checker_bonus(&v);
	cube3D_bonus(&v);
	mlx_put_image_to_window(v.mlx.mlx, v.mlx.mlx_win, v.mlx.img, 0, 0);
	mlx_loop_hook(v.mlx.mlx, loop_hook_bonus, &v);
	mlx_hook(v.mlx.mlx_win, 6, 0, mouse_hook, &v);
	mlx_hook(v.mlx.mlx_win, 2, 0, key_press, &v);
	mlx_hook(v.mlx.mlx_win, 3, 0, key_release, &v);
	mlx_hook(v.mlx.mlx_win, 17, 0, destroy, &v);
	mlx_loop(v.mlx.mlx);
}

// int	main(int ac, char **av)
// {
// 	t_data v;
// 	atexit(f);
// 	parsing_bonus(&v, ac, av);
// 	init_bonus(&v);
// 		checker_bonus(&v);
// 	int i = 0;
// 	 while (v.pars.map2[i])
//     {
//         printf("|%s|\n", v.pars.map2[i++]);
//     }
// 	printf("%s\n", v.pars.no);
// 	printf("%s\n", v.pars.so);
// 	printf("%s\n", v.pars.ea);
// 	printf("%s\n", v.pars.we);
// 	free_array(v.pars.map2);
// 	// free_array(v.pars.map);
// 	free(v.pars.so);
// 	free(v.pars.no);
// 	free(v.pars.ea);
// 	free(v.pars.we);
// 	free(v.sprite);
// 	free(v.sprt.sprite_buff);
// 	free(v.door.DOOR_buff);
//     printf("i = %d j = %d\n", v.pars.i, v.pars.j);
// }