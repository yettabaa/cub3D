/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 03:22:31 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/22 05:48:54 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	steps(t_data *v, double ang)
{
	t_norme1	n;

	n.y_hstp = v->scal;
	n.x_hstp = 0;
	(ang != 0 && ang != 180) && (n.x_hstp = v->scal / tan(rad(ang)));
	v->ryc.hdelta = (sqrt(pow(n.x_hstp, 2) + pow(n.y_hstp, 2)));
	n.var = floor(v->y / v->scal);
	n.y_h1stp = (v->y - (n.var * v->scal));
	(is(v, ang, DOWN) || !n.y_h1stp) && (n.y_h1stp = ((n.var * v->scal
					+ v->scal) - v->y));
	n.x_h1stp = 0;
	(ang != 0 && ang != 180) && (n.x_h1stp = n.y_h1stp / tan(rad(ang)));
	v->ryc.dhside = (sqrt(pow(n.x_h1stp, 2) + pow(n.y_h1stp, 2)));
	n.x_vstp = v->scal;
	n.y_vstp = v->scal * tan(rad(ang));
	(ang == 90 || ang == 270) && (n.y_vstp = 0);
	v->ryc.vdelta = (sqrt(pow(n.x_vstp, 2) + pow(n.y_vstp, 2)));
	n.var = floor(v->x / v->scal);
	n.x_v1stp = (v->x - n.var * v->scal);
	(is(v, ang, RIGHT)) && (n.x_v1stp = ((n.var * v->scal + v->scal) - v->x));
	(ang == 270 || ang == 90) && (n.x_v1stp = 0);
	n.y_v1stp = (n.x_v1stp * tan(rad((ang))));
	v->ryc.dvside = (sqrt(fabs(pow(n.x_v1stp, 2)) + fabs(pow(n.y_v1stp, 2))));
}

void	visualize_maps(t_data *v, double ang, int *i, int *j)
{
	*i = v->ryc.x / v->scal;
	*j = v->ryc.y / v->scal;
	(is(v, ang, LEFT)) && (*i = ((v->ryc.x) - v->epsil) / v->scal);
	(is(v, ang, RIGHT)) && (*i = (v->ryc.x + v->epsil) / v->scal);
	((is(v, ang, UP) || (int)ang == 180)) && (*j = (v->ryc.y - v->epsil)
			/ v->scal);
	((is(v, ang, DOWN) || !(int)ang)) && (*j = ((v->ryc.y) + v->epsil)
			/ v->scal);
}

static void	inc_smal_steps(t_data *v, double ang)
{
	int		i;
	int		j;
	int		iq;
	double	smal_sidstp;

	(v->ryc.vdelta <= v->ryc.hdelta) && (smal_sidstp = v->ryc.dvside);
	(v->ryc.vdelta > v->ryc.hdelta) && (smal_sidstp = v->ryc.dhside);
	v->ryc.x = v->x + (smal_sidstp * cos(rad(ang)));
	v->ryc.y = v->y + (smal_sidstp * sin(rad(ang)));
	visualize_maps(v, ang, &i, &j);
	v->ryc.smal_stp = smal_sidstp;
	iq = 1;
	while (check_(v, i, j, WALL))
	{
		v->ryc.smal_stp = iq * fmin(v->ryc.hdelta, v->ryc.vdelta) + smal_sidstp;
		v->ryc.x = v->x + (v->ryc.smal_stp * cos(rad(ang)));
		v->ryc.y = v->y + (v->ryc.smal_stp * sin(rad(ang)));
		visualize_maps(v, ang, &i, &j);
		iq++;
	}
}

static void	inc_big_steps(t_data *v, double ang)
{
	int		i;
	int		j;
	int		iq;
	double	big_sidstp;

	(v->ryc.vdelta <= v->ryc.hdelta) && (big_sidstp = v->ryc.dhside);
	(v->ryc.vdelta > v->ryc.hdelta) && (big_sidstp = v->ryc.dvside);
	v->ryc.x = v->x + (big_sidstp * cos(rad(ang)));
	v->ryc.y = v->y + (big_sidstp * sin(rad(ang)));
	visualize_maps(v, ang, &i, &j);
	v->ryc.big_stp = (big_sidstp);
	iq = 1;
	while (big_sidstp < v->ryc.smal_stp && check_(v, i, j, WALL))
	{
		v->ryc.big_stp = iq * fmax(v->ryc.hdelta, v->ryc.vdelta) + big_sidstp;
		v->ryc.x = v->x + (v->ryc.big_stp * cos(rad(ang)));
		v->ryc.y = v->y + (v->ryc.big_stp * sin(rad(ang)));
		visualize_maps(v, ang, &i, &j);
		iq++;
		if (v->ryc.big_stp > v->ryc.smal_stp || check_(v, i, j, 0))
			break ;
	}
}

double	raycasting(t_data *v, double ang)
{
	steps(v, ang);
	inc_smal_steps(v, ang);
	inc_big_steps(v, ang);
	v->raydis = fmin(v->ryc.smal_stp, v->ryc.big_stp);
	v->raydis_fishbowl = fmin(v->ryc.smal_stp, v->ryc.big_stp)
		* cos(rad(v->orientation - ang));
	if (v->ryc.big_stp > v->ryc.smal_stp && v->ryc.hdelta > v->ryc.vdelta
		+ v->epsil)
		v->tx.hitw = VER;
	else if (v->ryc.big_stp < v->ryc.smal_stp && v->ryc.hdelta
		+ v->epsil < v->ryc.vdelta)
		v->tx.hitw = VER;
	else if (v->ryc.big_stp > v->ryc.smal_stp && v->ryc.hdelta
		+ v->epsil < v->ryc.vdelta)
		v->tx.hitw = HORI;
	else if (v->ryc.big_stp < v->ryc.smal_stp && v->ryc.hdelta > v->ryc.vdelta
		+ v->epsil)
		v->tx.hitw = HORI;
	v->xw = v->x + (v->raydis * cos(rad(ang)));
	v->yw = v->y + (v->raydis * sin(rad(ang)));
	return (v->raydis);
}
