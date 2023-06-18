/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 22:58:38 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/18 04:43:57 by yettabaa         ###   ########.fr       */
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
    v->sprite[k].i = i;
    v->sprite[k].j = j;
    v->sprite[k].xs = i * v->scal + v->scal / 2;
    v->sprite[k].ys = j * v->scal + v->scal / 2;
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
    v->sprite_buff = malloc(sizeof(unsigned int *) * 4);
    if(!v->sprite_buff)
        ft_error("Allocate sprite buff failed");
    while (i <= 3)
    {
        // /Users/yettabaa/Desktop/cub3D/textures/kitty/front_00.xpm
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
    (x_texel = v->txt.width * (x - v->xs0) / v->spriteDimension);
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

void visible_sprite(t_data *v)
{
    int i = -1;

    while (++i < v->count_sprites)
    {
        if (fabs((normalize_angle_360(v->orientation) - normalize_angle_360(Deg(atan2(v->sprite[i].ys - v->y, v->sprite[i].xs - v->x))))) <= 30)
        {
            addobjt(&v->object, newsprite(v, v->sprite[i]));
        }
    }
    
}

void render_ssprite(t_data *v)
{
	double proj_sp;
    int xxx;
    
    (v->frames == 10001) && (v->frames = 0);
    (v->frames == 10000) && (v->ind_sprite_text += 1);
    (v->ind_sprite_text == 4) && (v->ind_sprite_text = 0);
    fill_sprite(v, v->ind_sprite_text % 4);
    v->frames += 1;
    // fill_sprite(v, 0);
    // disc(v, v->sprite[i].i * v->scal + v->scal / 2, v->sprite[i].j * v->scal + v->scal / 2, 0xff0000);
    // while (v->sprt)
    // {
	    v->spriteDimension = (v->scal / v->object->rydis) * v->disProj;
	    v->y0 = (HIGHT / 2) - (v->spriteDimension / 2);
	    v->y1 = v->y0 + v->spriteDimension;
        	// printf("%f\n", (Deg(atan2(v->object->y - v->y, v->object->x - v->x))) - (v->orientation));
        proj_sp = tan(Rad(v->object->angle)) * v->disProj;
	    v->xs0 = (WIDTH / 2) + proj_sp - (v->spriteDimension / 2);
	    v->xs1 = v->xs0 + v->spriteDimension;
        xxx = v->xs0;
	    // while (xxx < v->xs1)
	    // {
            // if ((xxx >= 0  && xxx <= 1600))
                // printf("xxx = %d rydxxx = %f ryd_o = %f\n",xxx, v->ryd[xxx], v->object->rydis);
                
            if(v->x_wind >= v->xs0  && v->x_wind <= v->xs1)
	    	    dda_sprite(v, v->y0, v->y1, v->x_wind);
	    // 	xxx++;
	    // }
        // v->object->rendered = 1;
        // v->sprt = v->sprt->next;
    // }
    
    // printf("xs0 = %f xs1 = %f demension = %f\n", v->xs0, v->xs1, v->spriteDimension);
    // (v->xs0 < 0) && (v->xs0 = 0);
	// (v->xs1 > WIDTH) && (v->xs1 = WIDTH);
    
    // for (int x = v->xs0; x < v->xs1; x++)
    //     for(int y = v->y0; y < v->y1; y++)
    //     {
    //         if (x >= 0 && x < WIDTH && y >= 0 && y < HIGHT)
    //             my_mlx_pixel_put(v, x, y, 0xff);
    //     } 
}