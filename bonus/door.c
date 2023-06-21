/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 23:47:25 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/22 00:14:44 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void get_text_door(t_data *v)
{
    int i;
	int endian;
    char *itoa;
    char *path;
    void *tx_img;
    
    i = 0;
    v->door.DOOR_buff = malloc(sizeof(unsigned int*) * 34);
    if (!v->door.DOOR_buff)
        ft_exit(v, "Error\nAllocate door buffer failed !", 1);
    while (i <= 32)
    {
        itoa = ft_itoa(i+1);
        path = ft_strjoin3("./Common/textures/DOOR/", itoa, ".xpm");
        tx_img =  mlx_xpm_file_to_image(v->mlx.mlx, path, &v->door.DOOR_width, &v->door.DOOR_height);
        free(itoa);
        free(path);
        if(!tx_img)
            ft_exit(v, "Error\nInvalid Door PATH !", 1);
        v->door.DOOR_buff[i++] = (unsigned int *)mlx_get_data_addr(tx_img, &endian, &v->door.DOOR_line, &endian);
    }

}

void fill_door(t_data *v, int ind)
{    
    v->txt.buff = v->door.DOOR_buff[ind];
    v->txt.width = v->door.DOOR_width;
    v->txt.height = v->door.DOOR_height;
    v->txt.line = v->door.DOOR_line;   
}

t_object *newdoor(t_data *v, double ryd, int flag)
{
    t_object *nd;
    (void)v;
    
    nd = malloc(sizeof(t_object));
    if (!nd)
        ft_exit(v, "Error\nAllocate new door failed !", 1);
	nd->type = DOOR;
	(flag == WALL) && (nd->type = WALL);
	nd->rydis = ryd;
    nd->rydis_fbw = ryd * cos(Rad(v->orientation - v->ryc.ang));
	(flag == HORI || flag == VER) && (nd->hitw = flag);
	nd->x = v->x + ryd * cos(Rad(v->ryc.ang));
	nd->y = v->y + ryd * sin(Rad(v->ryc.ang));
	nd->next = NULL;
    return(nd);
}

void	dda_door(t_data *v,t_object *object, double y0, double y1)
{
	int		i;
    int x_texel;
    int y_texel;
	double	steps;
	unsigned int color;
   
	(y0 < 0) && (y0 = 0);
	(y1 > HIGHT) && (y1 = HIGHT);
	steps = fabs(y0 - y1);
	i = 0;
    (object->hitw == VER) && (x_texel = v->txt.width * fmod(object->y , v->scal) / v->scal);
    (object->hitw == HORI) && (x_texel = v->txt.width * fmod(object->x , v->scal) / v->scal);
    (x_texel < 0) && (x_texel = 0);
    (x_texel > v->txt.width) && (x_texel = v->txt.width);
	while (i < steps)
	{
        y_texel = v->txt.height * (i + (fabs(v->y1 - v->y0 - steps) / 2)) / fabs(v->y1 - v->y0);
        (y_texel < 0) && (y_texel = 0);
        (y_texel > v->txt.height) && (y_texel = v->txt.height);
		color = v->txt.buff[y_texel * (v->txt.line / 4) + x_texel];
		((color >> 24 & 0x000000ff) != 255) && my_mlx_pixel_put(v ,(v->x_wind), (y0), color);
		y0++;
		i++;
	}
}
