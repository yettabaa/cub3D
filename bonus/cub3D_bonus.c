/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 00:26:29 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/17 22:04:02 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void init_bonus(t_data *v)
{
    v->epsilon = 1e-8; // ??? hit the wall in the origin axis  // (1,5) angle 225
    v->scal = 12; // 19
    v->orientation = strchr_c("WSEN", v->pars.palayer_dir) * 90;
    // v->orientation = 0;
    v->hook.angle_dir = 0;
    v->hook.angle_speed = 3;
    v->hook.walk_dir = 0;
    v->hook.walk_speed = 1.5;
    v->hook.angleOr = 0;
    v->disProj = (WIDTH / 2) / tan(Rad(30));
    v->x = (v->pars.x * v->scal + v->scal / 2);
    v->y = (v->pars.y * v->scal + v->scal / 2);
    v->frames = 0;
    v->ind_sprite_text = 0;
    get_textures(v);
    get_text_door(v);
    get_text_sprites(v);
    v->list_door = NULL;
}

void cube3D_bonus(t_data *v)
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
        raycasting_bonus(v, v->ryc.ang);
        render_wall_bonus(v, v->ryc.ang);
        vi += (double)60 / (double)WIDTH;
        v->x_wind += 1;
    }
    // fill_sprite(v, 0);	
	// int i = -1;
	// double sprtHeight;
	// double ang_sp;
	// double proj_sp;
    // double disProj = (WIDTH / 2) / tan(rad(30));
    // double xxx;
	// while (++i < v->count_sprites)
	// {
    //     double spriteDis = des_betw_2pt(v->sprite[i].xs, v->sprite[i].ys, v->x, v->y);
	// 	sprtHeight = (v->scal / spriteDis) * disProj;
	// 	v->y0 = (HIGHT / 2) - (sprtHeight / 2);
	// 	v->y1 = v->y0 + sprtHeight;
	// 	ang_sp = normalize_angle_360(radiansToDegrees(atan2(v->sprite[i].ys - v->y, v->sprite[i].xs - v->x))- v->orientation);
    //     // ang_sp -= v->orientation;
    //     printf("ang = %f ang 3ajiba  = %f (xs = %f, ys= %f)  (x = %f, y = %f)\n",v->orientation, (ang_sp), v->sprite[i].xs ,v->sprite[i].ys, v->x,v->y);
	// 	proj_sp = tan((rad(ang_sp))) * disProj;
	// 	v->xs0 = (WIDTH / 2) + proj_sp - (sprtHeight / 2);
	// 	v->xs1 = v->xs0 + sprtHeight;
    //     (v->xs0 < 0) && (v->xs0 = 0);
	//     (v->xs1 > WIDTH) && (v->xs1 = WIDTH);
        
    //     xxx = v->xs0;
	// 	// printf("= >%f wall \n", v->xrs);
	// 	while (xxx < v->xs1)
	// 	{
	// 		dda_sprite(v, v->y0, v->y1, xxx);
	// 		xxx++;
	// 	}
		
	// }
    mini_maps(v, 0x00ff00);
    render_ssprite(v);
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
    parsing_bonus(&v, ac, av); // rename// parsing bonus
    init_bonus(&v);
    player_position(&v);
    // if (v.sprite)
    //     printf("x = %f y = %f\n",  v.sprite[0].xs,  v.sprite[0].ys);
    cube3D_bonus(&v);
	mlx_put_image_to_window(v.mlx.mlx, v.mlx.mlx_win, v.mlx.img, 0, 0);
    mlx_loop_hook(v.mlx.mlx, loop_hook_bonus, &v);
    mlx_hook(v.mlx.mlx_win, 2, 0, key_press, &v);
    mlx_hook(v.mlx.mlx_win, 3, 0, key_release, &v);
    mlx_hook(v.mlx.mlx_win, 17, 0, destroy, &v);
	mlx_loop(v.mlx.mlx);
}