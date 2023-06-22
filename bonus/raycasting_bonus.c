/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 03:22:31 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/22 05:47:49 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	inc_smal_steps(t_data *v, t_object **object, double ang)
{
	t_norme	n;

	n.smal_sidstp = v->ryc.dvside;
	n.txw = VER;
	(v->ryc.vdelta > v->ryc.hdelta) && (n.smal_sidstp = v->ryc.dhside);
	(v->ryc.vdelta > v->ryc.hdelta) && (n.txw = HORI);
	v->ryc.x = v->x + (n.smal_sidstp * cos(rad(ang)));
	v->ryc.y = v->y + (n.smal_sidstp * sin(rad(ang)));
	visualize_maps(v, ang, &n.i, &n.j);
	v->ryc.smal_stp = n.smal_sidstp;
	if (check_(v, n.i, n.j, DOOR))
		addobjt(object, newdoor(v, n.smal_sidstp, n.txw));
	n.iq = 1;
	while (check_(v, n.i, n.j, WALL))
	{
		v->ryc.smal_stp = (n.iq++) * fmin(v->ryc.hdelta, v->ryc.vdelta)
			+ n.smal_sidstp;
		v->ryc.x = v->x + (v->ryc.smal_stp * cos(rad(ang)));
		v->ryc.y = v->y + (v->ryc.smal_stp * sin(rad(ang)));
		visualize_maps(v, ang, &n.i, &n.j);
		if (check_(v, n.i, n.j, DOOR))
			addobjt(object, newdoor(v, v->ryc.smal_stp, n.txw));
	}
}

static void	inc_big_steps(t_data *v, t_object **object, double ang)
{
	t_norme	n;

	n.big_sidstp = v->ryc.dhside;
	n.txw = HORI;
	(v->ryc.vdelta > v->ryc.hdelta) && (n.big_sidstp = v->ryc.dvside);
	(v->ryc.vdelta > v->ryc.hdelta) && (n.txw = VER);
	v->ryc.x = v->x + (n.big_sidstp * cos(rad(ang)));
	v->ryc.y = v->y + (n.big_sidstp * sin(rad(ang)));
	visualize_maps(v, ang, &n.i, &n.j);
	v->ryc.big_stp = n.big_sidstp;
	if (n.big_sidstp < v->ryc.smal_stp && check_(v, n.i, n.j, DOOR))
		addobjt(object, newdoor(v, n.big_sidstp, n.txw));
	n.iq = 1;
	while (n.big_sidstp < v->ryc.smal_stp && check_(v, n.i, n.j, WALL))
	{
		v->ryc.big_stp = (n.iq++) * fmax(v->ryc.hdelta, v->ryc.vdelta)
			+ n.big_sidstp;
		v->ryc.x = v->x + (v->ryc.big_stp * cos(rad(ang)));
		v->ryc.y = v->y + (v->ryc.big_stp * sin(rad(ang)));
		visualize_maps(v, ang, &n.i, &n.j);
		if (v->ryc.big_stp < v->ryc.smal_stp && check_(v, n.i, n.j, DOOR))
			addobjt(object, newdoor(v, v->ryc.big_stp, n.txw));
		if (v->ryc.big_stp > v->ryc.smal_stp || check_(v, n.i, n.j, 0))
			break ;
	}
}

double	raycasting_bonus(t_data *v, t_object **object, double ang)
{
	steps(v, ang);
	inc_smal_steps(v, object, ang);
	inc_big_steps(v, object, ang);
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
	addobjt(object, newdoor(v, v->raydis, WALL));
	return (v->raydis);
}
