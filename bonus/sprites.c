/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 22:58:38 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/19 01:39:09 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void get_text_sprites(t_data *v)
{
    int i;
    int endian;
    char *itoa;
    char *path;
    void *tx_img;

    i = 0;
    v->sprite_buff = malloc(sizeof(unsigned int *) * 4);
    if(!v->sprite_buff)
        ft_error("Allocate sprite buff failed");
    while (i <= 3)
    {
        itoa = ft_itoa(i);
        path = ft_strjoin3("./textures/kitty/front_0", itoa, ".xpm");
        //  printf("%s\n",path);
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

void	dda_sprite(t_data *v, double y0, double y1, int x) // opti
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
    (x_texel = v->txt.width * (x - v->xs0) / v->spriteDimension);
	while (i < steps)
	{
        y_texel = v->txt.height * (i + (fabs(v->y1 - v->y0 - steps) / 2)) / fabs(v->y1 - v->y0);
		color = v->txt.buff[y_texel * (v->txt.line / 4) + x_texel];
		if (x >= 0 && x < WIDTH && round(y0) >= 0 && round(y0) < HIGHT)
			((color >> 24 & 0x000000ff) != 255) && my_mlx_pixel_put(v ,x, y0, color);
		y0++;
		i++;
	}
}

t_object *visible_sprite(t_data *v)
{
    int i;
    double ang;
    t_object *visible_sprite;
    
    
    i = -1;
    visible_sprite = NULL;
    while (++i < v->count_sprites)
    {
        ang = fabs((normalize_angle_360(v->orientation) - normalize_angle_360(Deg(atan2(v->sprite[i].ys - v->y, v->sprite[i].xs - v->x)))));
        (ang > 330) && (ang -= 330);
        if (ang <= 30)
            addobjt(&visible_sprite, newsprite(v, v->sprite[i]));
    }
    return(visible_sprite);
}

void render_ssprite(t_data *v)
{
	double proj_sp;
    
    (v->frames == 9 * WIDTH + 1) && (v->frames = 0);
    (v->frames == 9 * WIDTH) && (v->ind_sprite_text += 1);
    (v->ind_sprite_text == 4) && (v->ind_sprite_text = 0);
    fill_sprite(v, v->ind_sprite_text % 4);
    v->frames += 1;
    // fill_sprite(v, 0);
    // disc(v, v->sprite[i].i * v->scal + v->scal / 2, v->sprite[i].j * v->scal + v->scal / 2, 0xff0000);
	v->spriteDimension = (v->scal / v->tmpobj->rydis) * v->disProj;
	v->y0 = (HIGHT / 2) - (v->spriteDimension / 2);
	v->y1 = v->y0 + v->spriteDimension;
    proj_sp = tan(Rad(v->tmpobj->angle)) * v->disProj;
	v->xs0 = (WIDTH / 2) + proj_sp - (v->spriteDimension / 2);
	v->xs1 = v->xs0 + v->spriteDimension;
    if(v->x_wind >= v->xs0  && v->x_wind <= v->xs1)
	    dda_sprite(v, v->y0, v->y1, v->x_wind);
}