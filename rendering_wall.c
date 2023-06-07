/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_wall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 00:27:41 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/07 05:17:06 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


void fill_textures(t_data *v)
{
    // printf("%s\n", v->pars.no);
    v->no_img =  mlx_xpm_file_to_image(v->mlx.mlx, v->pars.no, &v->no_width, &v->no_height);
    v->no_buff = (unsigned int *)mlx_get_data_addr(v->no_img, &v->no_bitspp, &v->no_line, &v->no_endian);
    // printf("buf = %u height = %d width = %d \n", (unsigned int)v->no_buff[257], v->no_height, v->no_width);

}

void rendering_wall(t_data *v)
{
    double disProj;
    double wall_hight;

    
    disProj = (WIDTH / 2) / tan(rad(30));
    wall_hight = (v->scal / v->raydis) * disProj;
    v->y0 = ((HIGHT) / 2) - (wall_hight / 2);
    v->y1 = v->y0 + wall_hight;
    // dda(v, v->x0, 0, v->x0, v->y0, v->pars.c);
    // dda(v, v->x0, v->y0, v->x0, v->y1, 2039583);
    dda_textures(v, v->x0, v->y0, v->x0, v->y1);
    // dda(v, v->x0, v->y1, v->x0, HIGHT - 1, v->pars.f);
    // dda(v,0,100 ,100,30,0xffffff);
}