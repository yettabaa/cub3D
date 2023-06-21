/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_wall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 00:27:41 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/21 19:18:10 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void get_textures(t_data *v)
{
    int bitspp;
	int endian;
    void *tx_img;
    
    
    tx_img =  mlx_xpm_file_to_image(v->mlx.mlx, v->pars.no, &v->txt.NO_width, &v->txt.NO_height);
    if(!tx_img)
        ft_exit(v, "Error\nInvalid NO PATH !", 1);
    v->txt.NO_buff = (unsigned int *)mlx_get_data_addr(tx_img, &bitspp, &v->txt.NO_line, &endian);
    tx_img =  mlx_xpm_file_to_image(v->mlx.mlx, v->pars.so, &v->txt.SO_width, &v->txt.SO_height);
    if(!tx_img)
        ft_exit(v, "Error\nInvalid SO PATH !", 1);
    v->txt.SO_buff = (unsigned int *)mlx_get_data_addr(tx_img, &bitspp, &v->txt.SO_line, &endian);
    tx_img =  mlx_xpm_file_to_image(v->mlx.mlx, v->pars.we, &v->txt.WE_width, &v->txt.WE_height);
    if(!tx_img)
        ft_exit(v, "Error\nInvalid WE PATH !", 1);
    v->txt.WE_buff = (unsigned int *)mlx_get_data_addr(tx_img, &bitspp, &v->txt.WE_line, &endian);
    tx_img =  mlx_xpm_file_to_image(v->mlx.mlx, v->pars.ea, &v->txt.EA_width, &v->txt.EA_height);
    if(!tx_img)
        ft_exit(v, "Error\nInvalid EA PATH !", 1);
    v->txt.EA_buff = (unsigned int *)mlx_get_data_addr(tx_img, &bitspp, &v->txt.EA_line, &endian);
}

void fill_textures(t_data *v, int flag)
{
    (flag == NO) && (v->txt.buff = v->txt.NO_buff);
    (flag == NO) && (v->txt.width = v->txt.NO_width);
    (flag == NO) && (v->txt.height = v->txt.NO_height);
    (flag == NO) && (v->txt.line = v->txt.NO_line);
    (flag == SO) && (v->txt.buff = v->txt.SO_buff);
    (flag == SO) && (v->txt.width = v->txt.SO_width);
    (flag == SO) && (v->txt.height = v->txt.SO_height);
    (flag == SO) && (v->txt.line = v->txt.SO_line);
    (flag == WE) && (v->txt.buff = v->txt.WE_buff);
    (flag == WE) && (v->txt.width = v->txt.WE_width);
    (flag == WE) && (v->txt.height =  v->txt.WE_height);
    (flag == WE) && (v->txt.line = v->txt.WE_line);
    (flag == EA) && (v->txt.buff = v->txt.EA_buff);
    (flag == EA) && (v->txt.width = v->txt.EA_width);
    (flag == EA) && (v->txt.height = v->txt.EA_height);
    (flag == EA) && (v->txt.line = v->txt.EA_line);
}
void	dda_textures(t_data *v, double y0, double y1, int flag)
{
	int		i;
    int x_texel;
    int y_texel;
	double	steps;
   
	(flag == CEIL && y1 < 0) && (y1 = 0);
	(flag == TEXT && y0 < 0) && (y0 = 0);
	(flag == TEXT && y1 > HIGHT) && (y1 = HIGHT);
	(flag == FLOOR && y0 > HIGHT) && (y0 = HIGHT);
	steps = fabs(y0 - y1);
	i = -1;
    (v->txt.hitWall == VER) && (x_texel = v->txt.width * fmod(v->yw - v->epsilon, v->scal) / v->scal);
    (v->txt.hitWall == HORI) && (x_texel = v->txt.width * fmod(v->xw - v->epsilon, v->scal) / v->scal);
    (x_texel < 0) && (x_texel = 0);
    (x_texel > v->txt.width) && (x_texel = v->txt.width);
	while (++i < steps)
	{
        y_texel = v->txt.height * (i + (fabs(v->y1 - v->y0 - steps) / 2)) / fabs(v->y1 - v->y0);
        (y_texel < 0) && (y_texel = 0);
        (y_texel > v->txt.height) && (y_texel = v->txt.height);
		(flag == TEXT) && (my_mlx_pixel_put(v ,round(v->x_wind), round(y0), v->txt.buff[y_texel * (v->txt.line / 4) + x_texel]));
		(flag == CEIL) && (my_mlx_pixel_put(v ,round(v->x_wind), round(y0), v->pars.c));
		(flag == FLOOR) && (my_mlx_pixel_put(v ,round(v->x_wind), round(y0), v->pars.f));
		y0++;
	}
}
void rendering_wall(t_data *v, double ang)
{
    double disProj;
    double wall_hight;
    
    disProj = (WIDTH / 2) / tan(Rad(30));
    wall_hight = (v->scal / v->raydis_fishbowl) * disProj;
    v->y0 = ((HIGHT) / 2) - (wall_hight / 2);
    v->y1 = v->y0 + wall_hight;
    if ((is(v, ang, UP) || (int)v->ryc.ang == 180) && v->txt.hitWall == HORI) 
        fill_textures(v, NO);
    else if ((is(v, ang, DOWN) ) && v->txt.hitWall == HORI) 
        fill_textures(v, SO);
    else if (is(v, ang, LEFT) && v->txt.hitWall == VER) 
        fill_textures(v, EA);
    else if ((is(v, ang, RIGHT)) && v->txt.hitWall == VER) 
        fill_textures(v, WE);
    dda_textures(v, 0, v->y0, CEIL);
    dda_textures(v, v->y0, v->y1, TEXT);
    dda_textures(v, v->y1, HIGHT, FLOOR);
}