/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 00:27:41 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/15 03:14:06 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


void get_text_door(t_data *v)
{
    int bitspp;
	int endian;
    void *tx_img;
    int i = 0;
    
    v->DOOR_buff = malloc(sizeof(unsigned int*) * 45);
    if (!v->DOOR_buff)
        ft_error("Allocate door buffer failed");
    while (i <= 44)
    {
        // printf("%s\n",ft_strjoin3("/Users/yettabaa/Desktop/cub3D/textures/door/door_", ft_itoa(i), ".xpm"));
        tx_img =  mlx_xpm_file_to_image(v->mlx.mlx, ft_strjoin3("/Users/yettabaa/Desktop/cub3D/textures/door/door_", ft_itoa(i), ".xpm"), &v->DOOR_width, &v->DOOR_height);
        if(!tx_img)
            ft_error("DOOR PATH");
        v->DOOR_buff[i++] = (unsigned int *)mlx_get_data_addr(tx_img, &bitspp, &v->DOOR_line, &endian);
    }

}

void fill_door(t_data *v, int ind)
{    
    v->buff = v->DOOR_buff[ind];
    v->width = v->DOOR_width;
    v->height = v->DOOR_height;
    v->line = v->DOOR_line;   
}


void render_wall_bonus(t_data *v)
{
    double disProj;
    double wall_hight;

    
    disProj = (WIDTH / 2) / tan(rad(30));
    wall_hight = (v->scal / v->raydis_fishbowl) * disProj;
    v->y0 = ((HIGHT) / 2) - (wall_hight / 2);
    v->y1 = v->y0 + wall_hight;
    if ((is(v, UP) || (int)v->ryc.ang == 180) && v->hitWall == HORI) 
        fill_textures(v, NO);
    else if ((is(v, DOWN) ) && v->hitWall == HORI) 
        fill_textures(v, SO);
    else if (is(v, LEFT) && v->hitWall == VER) 
        fill_textures(v, EA);
    else if ((is(v, RIGHT)) && v->hitWall == VER) 
        fill_textures(v, WE);
    dda_textures(v, v->y1, HIGHT, FLOOR);
    dda_textures(v, 0, v->y0, CEIL);
    render_door(v); // rename
    // dda_textures(v, v->y1, HIGHT, FLOOR);
    // dda_textures(v, 0, v->y0, CEIL);
}