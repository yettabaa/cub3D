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
	v->epsil = 1e-8;
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
	v->collect = NULL;
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

int	main(int ac, char **av)
{
	t_data v;

	v.mlx.mlx = mlx_init();
	v.mlx.mlx_win = mlx_new_window(v.mlx.mlx, WIDTH, HIGHT, "cub3D_bonus");
	parsing_bonus(&v, ac, av);
	init_bonus(&v);
	checker_bonus(&v);
	mlx_loop_hook(v.mlx.mlx, loop_hook_bonus, &v);
	mlx_hook(v.mlx.mlx_win, 6, 0, _mouse_hook, &v);
	mlx_hook(v.mlx.mlx_win, 2, 1L<<0, _press, &v);
	mlx_hook(v.mlx.mlx_win, 3, 1L<<1, _release, &v);
	mlx_hook(v.mlx.mlx_win, 17, 1L<<5, _destroy, &v);
	mlx_loop(v.mlx.mlx);
}
