/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 23:47:25 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/15 04:53:40 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_door *newdoor(t_data *v, double ryd, int flag)
{
    t_door *nd;
    (void)v;
    
    nd = malloc(sizeof(t_door));
    if (!nd)
        ft_error("Allocate new door failed");
	nd->type = DOOR;
	(flag == WALL) && (nd->type = WALL);
	nd->rydis = ryd;
    nd->rydis_fbw = ryd * cos(rad(v->orientation - v->ryc.ang));
	(flag == SMALL && v->ryc.Vdelta <= v->ryc.Hdelta) && (nd->hitw = VER);
    (flag == SMALL && v->ryc.Vdelta + v->epsilon> v->ryc.Hdelta) && (nd->hitw = HORI);
	(flag == BIG && v->ryc.Vdelta <= v->ryc.Hdelta) && (nd->hitw = HORI);
    (flag == BIG && v->ryc.Vdelta + v->epsilon> v->ryc.Hdelta) && (nd->hitw = VER);
	(flag == WALL) && (nd->hitw = v->hitWall);
	nd->xd = v->x + ryd * cos(rad(v->ryc.ang));
	nd->yd = v->y + ryd * sin(rad(v->ryc.ang));
	nd->next = NULL;
    return(nd);    
}

void	addoor(t_door **lst, t_door *new)
{
	if (!lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	new->next = *lst;
	*lst = new;
}

void	dda_door(t_data *v, double y0, double y1) // opti
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
    (v->door->hitw == VER) && (x_texel = v->width * fmod(v->door->yd , v->scal) / v->scal);
    (v->door->hitw == HORI) && (x_texel = v->width * fmod(v->door->xd , v->scal) / v->scal);
	while (i < steps)
	{
        y_texel = v->height * (i + (fabs(v->y1 - v->y0 - steps) / 2)) / fabs(v->y1 - v->y0);
		color = v->buff[y_texel * (v->line / 4) + x_texel];
		if (round(v->x0) >= 0 && round(v->x0) < WIDTH && round(y0) >= 0 && round(y0) < HIGHT)
			((color >> 24 & 0x000000ff) != 255) && my_mlx_pixel_put(v ,(v->x0), (y0), color);
		y0 = y0 + yinc;
		i++;
	}
}

void text_door(t_data *v)
{
	double disProj;
    double wall_hight;
	double ration;

    disProj = (WIDTH / 2) / tan(rad(30));
    wall_hight = (v->scal / v->door->rydis_fbw) * disProj;
    v->y0 = ((HIGHT) / 2) - (wall_hight / 2);
    v->y1 = v->y0 + wall_hight;
	if (v->door->type == DOOR && v->door->rydis_fbw < v->raydis_fishbowl)
	{
		ration = 1 - ((v->door->rydis) / (2 * v->scal));
		(ration - v->epsilon < 0) && (ration = 0);
		(ration + v->epsilon > 1) && (ration = 1);
		printf("ang %f\n", normalize_angle_360(v->orientation));
		//  (printf("ration = %f  ryd_door = %f hdelta = %f\n", ration, v->door->raydis_door, v->ryc.Hdelta));
		fill_door(v, (ration + v->epsilon) * 43);
    	dda_door(v, v->y0, v->y1);
		
	}
	else
		dda_textures(v, v->y0, v->y1, TEXT);	
}

void swad_data(t_door *a, t_door *b)
{
	int c;
	double tmp;

	tmp = a->rydis_fbw;
	a->rydis_fbw = b->rydis_fbw;
	b->rydis_fbw = tmp;
	tmp = a->xd;
	a->xd = b->xd;
	b->xd = tmp;
	tmp = a->yd;
	a->yd = b->yd;
	b->yd = tmp;
	c = a->hitw;
	a->hitw = b->hitw;
	b->hitw = c;
	c = a->type;
	a->type = b->type;
	b->type = c;
}

void render_door(t_data *v)
{
	t_door *tmp;
	t_door tmp_v2;

	while (v->door)
	{
		tmp = v->door;
		while (tmp)
		{
			if (v->door->rydis_fbw < tmp->rydis_fbw)
			{
				ft_memmove(&tmp_v2, tmp , sizeof(t_door) - sizeof(void *));
				ft_memmove(tmp, v->door , sizeof(t_door) - sizeof(void *));
				ft_memmove(v->door, &tmp_v2, sizeof(t_door) - sizeof(void *));
			}
				// swad_data(v->door, tmp);
			tmp = tmp->next;
		}
		text_door(v);
		v->door = v->door->next;
	}
	v->door = NULL;
}