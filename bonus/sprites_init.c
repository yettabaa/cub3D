/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 02:19:46 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/22 00:13:16 by yettabaa         ###   ########.fr       */
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
    v->sprt.sprite_buff = malloc(sizeof(unsigned int *) * 5);
    if(!v->sprt.sprite_buff)
        ft_exit(v, "Error\nAllocate sprite buff failed !", 1);
    while (i <= 4)
    { //Users/yettabaa/Desktop/cub3D/textures/sprite/0.xpm
        itoa = ft_itoa(i);
        path = ft_strjoin3("./Common/textures/sprite/", itoa, ".xpm");
        //  printf("%s\n",path);
        tx_img = mlx_xpm_file_to_image(v->mlx.mlx, path, &v->sprt.sprite_width, &v->sprt.sprite_height);
        free(itoa);
        free(path);
        if(!tx_img)
            ft_exit(v, "Error\nInvalid Sprite PATH !", 1);
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

t_object *newsprite(t_data *v, t_GetSprites sprite)
{
    t_object *node;
	double FOV_angle ;
	double ProjP_sprite;
    
    node = malloc(sizeof(t_object));
    if (!node)
        ft_exit(v, "Error\nAllocate new sprite failed !", 1);
	node->type = SPRITE;
	FOV_angle = Deg(atan2(sprite.ys - v->y, sprite.xs - v->x)) - (v->orientation);
	ProjP_sprite = tan(Rad(FOV_angle)) * v->ProjPlane;
    node->x = sprite.xs;
    node->y = sprite.ys;
	node->rydis_fbw = des_betw_2pt(sprite.xs, sprite.ys, v->x, v->y) * cos(Rad(FOV_angle));
	node->Diemension = (v->scal / node->rydis_fbw) * v->ProjPlane;
	node->y0 = (HIGHT / 2) - (node->Diemension / 2);
	node->y1 = node->y0 + node->Diemension;
	node->x0 = (WIDTH / 2) + ProjP_sprite - (node->Diemension / 2);
	node->x1 = node->x0 + node->Diemension;
	// printf("x = %f y = %f ryd = %f\n", sprite.xs, sprite.ys, node->rydis_fbw);
	node->next = NULL;
    return(node);
}