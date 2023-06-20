/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 02:19:46 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/20 02:22:40 by yettabaa         ###   ########.fr       */
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
    v->sprt.sprite_buff = malloc(sizeof(unsigned int *) * 4);
    if(!v->sprt.sprite_buff)
        ft_error("Allocate sprite buff failed");
    while (i <= 3)
    {
        itoa = ft_itoa(i);
        path = ft_strjoin3("./textures/kitty/front_0", itoa, ".xpm");
        //  printf("%s\n",path);
        tx_img = mlx_xpm_file_to_image(v->mlx.mlx, path, &v->sprt.sprite_width, &v->sprt.sprite_height);
        free(itoa);
        free(path);
        if(!tx_img)
            ft_error("Sprite PATH");
        v->sprt.sprite_buff[i++] = (unsigned int *)mlx_get_data_addr(tx_img, &endian,  &v->sprt.sprite_line, &endian);
    }
}

void fill_sprite(t_data *v, int ind)
{
    v->txt.buff = v->sprt.sprite_buff[ind];
    v->txt.width = v->sprt.sprite_width;
    v->txt.height = v->sprt.sprite_height;
    v->txt.line = v->sprt.sprite_line;
}

void _sprites(t_data *v ,int k, int i, int j)
{
    v->sprite[k].i = i;
    v->sprite[k].j = j;
    v->sprite[k].xs = i * v->scal + v->scal / 2;
    v->sprite[k].ys = j * v->scal + v->scal / 2;
}