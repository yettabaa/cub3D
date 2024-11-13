/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 23:47:25 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/22 05:54:08 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_text_door(t_data *v)
{
	int		i;
	int		endian;
	char	*itoa;
	char	*path;
	void	*tx_img;

	i = 0;
	v->door.door_buff = malloc(sizeof(unsigned int *) * 33);
	if (!v->door.door_buff)
		my_exit(v, "Error\nAllocate door buffer failed !", 1);
	while (i < 33)
	{
		itoa = ft_itoa(i + 1);
		path = ft_strjoin3("./Common/textures/DOOR/", itoa, ".xpm");
		tx_img = mlx_xpm_file_to_image(v->mlx.mlx, path, &v->door.door_width,
				&v->door.door_height);
		free(itoa);
		free(path);
		if (!tx_img)
			my_exit(v, "Error\nInvalid Door PATH !", 1);
		v->door.door_buff[i++] = (unsigned int *)mlx_get_data_addr(tx_img,
				&endian, &v->door.door_line, &endian);
		collect_node(&v->collect, creat_node(v, tx_img));
	}
}

void	fill_door(t_data *v, int ind)
{
	v->tx.buff = v->door.door_buff[ind];
	v->tx.width = v->door.door_width;
	v->tx.height = v->door.door_height;
	v->tx.line = v->door.door_line;
}

t_object	*newdoor(t_data *v, double ryd, int flag)
{
	t_object	*nd;

	nd = malloc(sizeof(t_object));
	if (!nd)
		my_exit(v, "Error\nAllocate new door failed !", 1);
	nd->type = DOOR;
	(flag == WALL) && (nd->type = WALL);
	nd->rydis = ryd;
	nd->rydis_fbw = ryd * cos(rad(v->orientation - v->ryc.ang));
	(flag == HORI || flag == VER) && (nd->hitw = flag);
	nd->x = v->x + ryd * cos(rad(v->ryc.ang));
	nd->y = v->y + ryd * sin(rad(v->ryc.ang));
	nd->next = NULL;
	return (nd);
}

void	dda_door(t_data *v, t_object *object, double y0, double y1)
{
	int				i;
	int				x_texel;
	int				y_texel;
	double			steps;
	unsigned int	c;

	(y0 < 0) && (y0 = 0);
	(y1 > HIGHT) && (y1 = HIGHT);
	steps = fabs(y0 - y1);
	i = -1;
	(object->hitw == VER) && (x_texel = v->tx.width * fmod(object->y, v->scal)
			/ v->scal);
	(object->hitw == HORI) && (x_texel = v->tx.width * fmod(object->x, v->scal)
			/ v->scal);
	(x_texel < 0) && (x_texel = 0);
	(x_texel > v->tx.width) && (x_texel = v->tx.width);
	while (++i < steps)
	{
		y_texel = v->tx.height * (i + (fabs(v->y1 - v->y0 - steps) / 2))
			/ fabs(v->y1 - v->y0);
		(y_texel < 0) && (y_texel = 0);
		(y_texel > v->tx.height) && (y_texel = v->tx.height);
		c = v->tx.buff[y_texel * (v->tx.line / 4) + x_texel];
		((c >> 24 & 0x000000ff) != 255) && my_pixel_put(v, v->x_wind, y0++, c);
	}
}
