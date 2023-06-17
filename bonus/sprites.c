/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 22:58:38 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/17 05:50:04 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double des_betw_2pt(double x0, double y0, double x1, double y1)
{
    return(sqrt(pow(fabs(x0 - x1), 2) + pow(fabs(y0 - y1), 2)));
}

void _sprites(t_data *v ,int k, int i, int j)
{
    // printf("%d   %d\n", v->pars.x, v->pars.y);
    // printf("i = %d   j = %d k = %d\n", i ,j, k);
    v->sprite[k].xs = j * v->scal + v->scal / 2;
    v->sprite[k].ys = i * v->scal + v->scal / 2;
            // printf("x = %f y = %f\n",  v->sprite[k].xs,  v->sprite[k].ys);
    v->sprite[k].rydis = des_betw_2pt(v->sprite[k].xs, v->sprite[k].ys, v->x, v->y);
}

void get_text_sprites(t_data *v)
{
    int i;
    int endian;
    char *itoa;
    char *path;
    void *tx_img;

    i = 0;
    v->sprite_buff = malloc(sizeof(unsigned int *) * 6);
    if(!v->sprite_buff)
        ft_error("Allocate sprite buff failed");
    while (i <= 5)
    {
        itoa = ft_itoa(i);
        path = ft_strjoin3("./textures/sprite/R", itoa, ".xpm");
         // printf("%s\n",path);
        tx_img = mlx_xpm_file_to_image(v->mlx.mlx, path, &v->sprite_width, &v->sprite_height);
        free(itoa);
        free(path);
        if(!tx_img)
            ft_error("Sprite PATH");
        v->sprite_buff[i++] = (unsigned int *)mlx_get_data_addr(tx_img, &endian,  &v->sprite_line, &endian);
    }
}

void fill_sprite(t_data *v, int ind)
{
    v->txt.buff = v->sprite_buff[ind];
    v->txt.width = v->sprite_width;
    v->txt.height = v->sprite_height;
    v->txt.line = v->sprite_line;
}

void	dda_sprite(t_data *v, double y0, double y1, double x) // opti
{
    int		i;
    int x_texel;
    int y_texel;
	double	yinc;
	double	steps;
	unsigned int color;
   
	(y0 < 0) && (y0 = 0);
	(y1 > HIGHT) && (y1 = HIGHT);
	steps = fabs(y0 - y1);
	yinc = (y1 - y0) / steps;
	i = 0;
    // (v->list_door->hitw == VER) && (x_texel = v->txt.width * fmod(v->list_door->y , v->scal) / v->scal);
    (x_texel = v->txt.width * fmod(x , v->scal) / v->scal);
    // x_texel = fmod(x , v->txt.width);
	while (i < steps)
	{
        y_texel = v->txt.height * (i + (fabs(v->y1 - v->y0 - steps) / 2)) / fabs(v->y1 - v->y0);
		color = v->txt.buff[y_texel * (v->txt.line / 4) + x_texel];
		if (round(x) >= 0 && round(x) < WIDTH && round(y0) >= 0 && round(y0) < HIGHT)
			((color >> 24 & 0x000000ff) != 255) && my_mlx_pixel_put(v ,(x), (y0), color);
		y0 = y0 + yinc;
		i++;
	}
}