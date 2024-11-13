/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 02:19:46 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/22 19:56:07 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <mlx_int.h>

void	get_text_sprites(t_data *v)
{
	int		i;
	int		endian;
	char	*itoa;
	char	*path;
	void	*tx_img;

	i = 0;
	v->sprt.sprite_buff = malloc(sizeof(unsigned int *) * 5);
	if (!v->sprt.sprite_buff)
		my_exit(v, "Error\nAllocate sprite buff failed !", 1);
	while (i < 5)
	{
		itoa = ft_itoa(i);
		path = ft_strjoin3("./Common/textures/sprite/", itoa, ".xpm");
		tx_img = mlx_xpm_file_to_image(v->mlx.mlx, path, &v->sprt.sprite_width,
				&v->sprt.sprite_height);
		free(itoa);
		free(path);
		if (!tx_img)
			my_exit(v, "Error\nInvalid Sprite PATH !", 1);
		v->sprt.sprite_buff[i++] = (unsigned int *)mlx_get_data_addr(tx_img,
				&endian, &v->sprt.sprite_line, &endian);
		collect_node(&v->collect, creat_node(v, tx_img));
	}
}

void	fill_sprite(t_data *v, int ind)
{
	v->tx.buff = v->sprt.sprite_buff[ind];
	v->tx.width = v->sprt.sprite_width;
	v->tx.height = v->sprt.sprite_height;
	v->tx.line = v->sprt.sprite_line;
}

int	_sprites(t_data *v, int k, int i, int j)
{
	v->sprite[k].i = i;
	v->sprite[k].j = j;
	v->sprite[k].xs = i * v->scal + v->scal / 2;
	v->sprite[k].ys = j * v->scal + v->scal / 2;
	return (1);
}

t_object	*newsprite(t_data *v, t_GetSprites sprite)
{
	t_object	*node;
	double		fov_angle;
	double		sprite_screen_post;

	node = malloc(sizeof(t_object));
	if (!node)
		my_exit(v, "Error\nAllocate new sprite failed !", 1);
	node->type = SPRITE;
	fov_angle = _deg(atan2(sprite.ys - v->y, sprite.xs - v->x))
		- v->orientation;
	sprite_screen_post = tan(rad(fov_angle)) * v->projplane;
	node->x = sprite.xs;
	node->y = sprite.ys;
	node->rydis_fbw = des_betw_2pt(sprite.xs, sprite.ys, v->x, v->y)
		* cos(rad(fov_angle));
	node->diemension = (v->scal / node->rydis_fbw) * v->projplane;
	node->y0 = (HIGHT / 2) - (node->diemension / 2);
	node->y1 = node->y0 + node->diemension;
	node->x0 = (WIDTH / 2) + sprite_screen_post - (node->diemension / 2);
	node->x1 = node->x0 + node->diemension;
	node->next = NULL;
	return (node);
}
