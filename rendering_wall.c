/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_wall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 00:27:41 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/13 02:54:45 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


void init_textures(t_data *v)
{
    int bitspp;
	int endian;
    void *tx_img;
    
    tx_img =  mlx_xpm_file_to_image(v->mlx.mlx, v->pars.no, &v->NO_width, &v->NO_height);
    if(!tx_img)
        ft_error("NO PATH");
    v->NO_buff = (unsigned int *)mlx_get_data_addr(tx_img, &bitspp, &v->NO_line, &endian); // get buff of colors
    
    // printf("%s\n", v->pars.so);
    tx_img =  mlx_xpm_file_to_image(v->mlx.mlx, v->pars.so, &v->SO_width, &v->SO_height);
    // printf("so_w = %d so_h = %d\n", v->SO_width, v->SO_height);
    if(!tx_img)
        ft_error("SO PATH");
    v->SO_buff = (unsigned int *)mlx_get_data_addr(tx_img, &bitspp, &v->SO_line, &endian);
    
    tx_img =  mlx_xpm_file_to_image(v->mlx.mlx, v->pars.we, &v->WE_width, &v->WE_height);
    if(!tx_img)
        ft_error("WE PATH");
    v->WE_buff = (unsigned int *)mlx_get_data_addr(tx_img, &bitspp, &v->WE_line, &endian);
    
    tx_img =  mlx_xpm_file_to_image(v->mlx.mlx, v->pars.ea, &v->EA_width, &v->EA_height);
    if(!tx_img)
        ft_error("EA PATH");
    v->EA_buff = (unsigned int *)mlx_get_data_addr(tx_img, &bitspp, &v->EA_line, &endian);
    
    tx_img =  mlx_xpm_file_to_image(v->mlx.mlx, "./textures/door/door_00.xpm", &v->DOOR_width, &v->DOOR_height);
    if(!tx_img)
        ft_error("DOOR PATH");
    v->DOOR_buff = (unsigned int *)mlx_get_data_addr(tx_img, &bitspp, &v->DOOR_line, &endian);
    // printf("buf = %u height = %d width = %d \n", (unsigned int)v->no_buff[257], v->no_height, v->no_width);

}

void fill_textures(t_data *v, int flag)
{
    (flag == NO) && (v->buff = v->NO_buff);
    (flag == NO) && (v->width = v->NO_width);
    (flag == NO) && (v->height = v->NO_height);
    (flag == NO) && (v->line = v->NO_line);
    
    (flag == SO) && (v->buff = v->SO_buff);
    (flag == SO) && (v->width = v->SO_width);
    (flag == SO) && (v->height = v->SO_height);
    (flag == SO) && (v->line = v->SO_line);
    
    (flag == WE) && (v->buff = v->WE_buff);
    (flag == WE) && (v->width = v->WE_width);
    (flag == WE) && (v->height =  v->WE_height);
    (flag == WE) && (v->line = v->WE_line);
    
    (flag == EA) && (v->buff = v->EA_buff);
    (flag == EA) && (v->width = v->EA_width);
    (flag == EA) && (v->height = v->EA_height);
    (flag == EA) && (v->line = v->EA_line);
    
    (flag == DOOR) && (v->buff = v->DOOR_buff);
    (flag == DOOR) && (v->width = v->DOOR_width);
    (flag == DOOR) && (v->height = v->DOOR_height);
    (flag == DOOR) && (v->line = v->DOOR_line);
    
}

void rendering_wall(t_data *v)
{
    double disProj;
    double wall_hight;

    
    disProj = (WIDTH / 2) / tan(rad(30));
    wall_hight = (v->scal / v->raydis_fishbowl) * disProj;
    v->y0 = ((HIGHT) / 2) - (wall_hight / 2);
    v->y1 = v->y0 + wall_hight;
    // printf("y0 = %f y1 = %f\n", v->y0, v->y1);
    if ((is(v, UP) || (int)v->ryc.ang == 180) && v->hitWall == HORI) 
        fill_textures(v, NO);
    else if ((is(v, DOWN) ) && v->hitWall == HORI) 
        fill_textures(v, SO);
    else if (is(v, LEFT) && v->hitWall == VER) 
        fill_textures(v, EA);
    else if ((is(v, RIGHT)) && v->hitWall == VER) 
        fill_textures(v, WE);
    dda_textures(v, 0, v->y0, CEIL);
    dda_textures(v, v->y0, v->y1, TEXT);
    if (v->hit == DOOR)
    {
        fill_textures(v, DOOR);
        dda_textures(v, v->y0, v->y1, TEXT);
    }
    dda_textures(v, v->y1, HIGHT, FLOOR);
}