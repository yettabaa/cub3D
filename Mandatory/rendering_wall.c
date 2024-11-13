/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_wall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 00:27:41 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/22 05:52:20 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_textures(t_data *v)
{
	int		b;
	void	*tx_img;

	tx_img = mlx_xpm_file_to_image(v->mlx.mlx, v->pars.no, &v->tx.nowdt,
			&v->tx.noh);
	if (!tx_img)
		my_exit(v, "Error\nInvalid NO PATH !", 1);
	v->tx.nob = (unsigned int *)mlx_get_data_addr(tx_img, &b, &v->tx.nol, &b);
	collect_node(&v->collect, creat_node(v, tx_img));
	tx_img = mlx_xpm_file_to_image(v->mlx.mlx, v->pars.so, &v->tx.sow,
			&v->tx.soh);
	if (!tx_img)
		my_exit(v, "Error\nInvalid SO PATH !", 1);
	v->tx.sob = (unsigned int *)mlx_get_data_addr(tx_img, &b, &v->tx.sol, &b);
	collect_node(&v->collect, creat_node(v, tx_img));
	tx_img = mlx_xpm_file_to_image(v->mlx.mlx, v->pars.we, &v->tx.wew,
			&v->tx.weh);
	if (!tx_img)
		my_exit(v, "Error\nInvalid WE PATH !", 1);
	v->tx.web = (unsigned int *)mlx_get_data_addr(tx_img, &b, &v->tx.wel, &b);
	collect_node(&v->collect, creat_node(v, tx_img));
	tx_img = mlx_xpm_file_to_image(v->mlx.mlx, v->pars.ea, &v->tx.eaw,
			&v->tx.eah);
	if (!tx_img)
		my_exit(v, "Error\nInvalid EA PATH !", 1);
	v->tx.eab = (unsigned int *)mlx_get_data_addr(tx_img, &b, &v->tx.wal, &b);
	collect_node(&v->collect, creat_node(v, tx_img));
}

void	fill_textures(t_data *v, int flag)
{
	(flag == NO) && (v->tx.buff = v->tx.nob);
	(flag == NO) && (v->tx.width = v->tx.nowdt);
	(flag == NO) && (v->tx.height = v->tx.noh);
	(flag == NO) && (v->tx.line = v->tx.nol);
	(flag == SO) && (v->tx.buff = v->tx.sob);
	(flag == SO) && (v->tx.width = v->tx.sow);
	(flag == SO) && (v->tx.height = v->tx.soh);
	(flag == SO) && (v->tx.line = v->tx.sol);
	(flag == WE) && (v->tx.buff = v->tx.web);
	(flag == WE) && (v->tx.width = v->tx.wew);
	(flag == WE) && (v->tx.height = v->tx.weh);
	(flag == WE) && (v->tx.line = v->tx.wel);
	(flag == EA) && (v->tx.buff = v->tx.eab);
	(flag == EA) && (v->tx.width = v->tx.eaw);
	(flag == EA) && (v->tx.height = v->tx.eah);
	(flag == EA) && (v->tx.line = v->tx.wal);
}

void	dda_textures(t_data *v, double y0, double y1, int flag)
{
	t_norme2	n;

	(flag == CEIL && y1 < 0) && (y1 = 0);
	(flag == TEXT && y0 < 0) && (y0 = 0);
	(flag == TEXT && y1 > HIGHT) && (y1 = HIGHT);
	(flag == FLOOR && y0 > HIGHT) && (y0 = HIGHT);
	n.steps = fabs(y0 - y1);
	n.i = -1;
	(v->tx.hitw == VER) && (n.xtx = v->tx.width * fmod(v->yw, v->scal)
			/ v->scal);
	(v->tx.hitw == HORI) && (n.xtx = v->tx.width * fmod(v->xw, v->scal)
			/ v->scal);
	(n.xtx < 0) && (n.xtx = 0);
	(n.xtx > v->tx.width) && (n.xtx = v->tx.width);
	while (++n.i < n.steps)
	{
		n.ytx = v->tx.height * (n.i + (fabs(v->y1 - v->y0 - n.steps) / 2))
			/ fabs(v->y1 - v->y0);
		(n.ytx < 0) && (n.ytx = 0);
		(n.ytx > v->tx.height) && (n.ytx = v->tx.height);
		(flag == TEXT) && (my_pixel_put(v, v->x_wind, y0++, v->tx.buff[n.ytx
					* (v->tx.line / 4) + n.xtx]));
		(flag == CEIL) && (my_pixel_put(v, v->x_wind, y0++, v->pars.c));
		(flag == FLOOR) && (my_pixel_put(v, v->x_wind, y0++, v->pars.f));
	}
}

void	rendering_wall(t_data *v, double ang)
{
	double	dis_proj;
	double	wall_hight;

	dis_proj = (WIDTH / 2) / tan(rad(30));
	wall_hight = (v->scal / v->raydis_fishbowl) * dis_proj;
	v->y0 = ((HIGHT) / 2) - (wall_hight / 2);
	v->y1 = v->y0 + wall_hight;
	if ((is(v, ang, UP) || (int)v->ryc.ang == 180) && v->tx.hitw == HORI)
		fill_textures(v, NO);
	else if ((is(v, ang, DOWN)) && v->tx.hitw == HORI)
		fill_textures(v, SO);
	else if (is(v, ang, LEFT) && v->tx.hitw == VER)
		fill_textures(v, EA);
	else if ((is(v, ang, RIGHT)) && v->tx.hitw == VER)
		fill_textures(v, WE);
	dda_textures(v, 0, v->y0, CEIL);
	dda_textures(v, v->y0, v->y1, TEXT);
	dda_textures(v, v->y1, HIGHT, FLOOR);
}
