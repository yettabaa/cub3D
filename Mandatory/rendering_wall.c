/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_wall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 00:27:41 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/16 19:18:18 by yettabaa         ###   ########.fr       */
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
        ft_error("NO PATH");
    v->txt.NO_buff = (unsigned int *)mlx_get_data_addr(tx_img, &bitspp, &v->txt.NO_line, &endian); // get buff of colors
    tx_img =  mlx_xpm_file_to_image(v->mlx.mlx, v->pars.so, &v->txt.SO_width, &v->txt.SO_height);
    if(!tx_img)
        ft_error("SO PATH");
    v->txt.SO_buff = (unsigned int *)mlx_get_data_addr(tx_img, &bitspp, &v->txt.SO_line, &endian);
    tx_img =  mlx_xpm_file_to_image(v->mlx.mlx, v->pars.we, &v->txt.WE_width, &v->txt.WE_height);
    if(!tx_img)
        ft_error("WE PATH");
    v->txt.WE_buff = (unsigned int *)mlx_get_data_addr(tx_img, &bitspp, &v->txt.WE_line, &endian);
    tx_img =  mlx_xpm_file_to_image(v->mlx.mlx, v->pars.ea, &v->txt.EA_width, &v->txt.EA_height);
    if(!tx_img)
        ft_error("EA PATH");
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

void rendering_wall(t_data *v, double ang)
{
    double disProj;
    double wall_hight;
    
    disProj = (WIDTH / 2) / tan(rad(30));
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