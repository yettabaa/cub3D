/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 23:47:25 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/14 05:50:28 by yettabaa         ###   ########.fr       */
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
    nd->raydis_door = ryd * cos(rad(v->orientation - v->ryc.ang));
	(flag == SMALL && v->ryc.Vdelta <= v->ryc.Hdelta) && (nd->hitw = VER);
    (flag == SMALL && v->ryc.Vdelta > v->ryc.Hdelta) && (nd->hitw = HORI);
	(flag == BIG && v->ryc.Vdelta <= v->ryc.Hdelta) && (nd->hitw = HORI);
    (flag == BIG && v->ryc.Vdelta > v->ryc.Hdelta) && (nd->hitw = VER);
	(flag == WALL) && (nd->hitw = v->hitWall);
	nd->xd = v->x + nd->raydis_door * cos(rad(v->ryc.ang));
	nd->yd = v->y + nd->raydis_door * sin(rad(v->ryc.ang));
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

void	dda_door(t_data *v, double y0, double y1, int flag) // opti
{
	int		i;
    int x_texel;
    int y_texel;
	double	yinc;
	double	steps;
   
	(flag == CEIL && y1 < 0) && (y1 = 0); // in case if we so cloose of the wall
	(flag == TEXT && y0 < 0) && (y0 = 0);
	(flag == TEXT && y1 > HIGHT) && (y1 = HIGHT);
	(flag == FLOOR && y0 > HIGHT) && (y0 = HIGHT);
	steps = fabs(y0 - y1);
	yinc = (y1 - y0) / steps;
	i = 0;
    (v->door->hitw == VER) && (x_texel = v->width * fmod(v->door->yd , v->scal) / v->scal);
    (v->door->hitw == HORI) && (x_texel = v->width * fmod(v->door->xd , v->scal) / v->scal);
	while (i < steps)
	{
        y_texel = v->height * (i + (fabs(v->y1 - v->y0 - steps) / 2)) / fabs(v->y1 - v->y0);
		if (round(v->x0) >= 0 && round(v->x0) < WIDTH && round(y0) >= 0 && round(y0) < HIGHT)
		{
			(flag == TEXT) && (my_mlx_pixel_put(v ,round(v->x0), round(y0), v->buff[y_texel * (v->line / 4) + x_texel]));
			(flag == CEIL) && (my_mlx_pixel_put(v ,round(v->x0), round(y0), v->pars.c));
			(flag == FLOOR) && (my_mlx_pixel_put(v ,round(v->x0), round(y0), v->pars.f));
		}
		y0 = y0 + yinc;
		i++;
	}
}
void text_door(t_data *v)
{
	double disProj;
    double wall_hight;

    disProj = (WIDTH / 2) / tan(rad(30));
    wall_hight = (v->scal / v->door->raydis_door) * disProj;
    v->y0 = ((HIGHT) / 2) - (wall_hight / 2);
    v->y1 = v->y0 + wall_hight;
	if (v->door->type == DOOR && v->door->raydis_door < v->raydis_fishbowl)
	{
		fill_door(v);
    	dda_door(v, v->y0, v->y1, TEXT);
	}
	else
		dda_textures(v, v->y0, v->y1, TEXT);	
}

void swad_data(t_door *a, t_door *b)
{
	int c;
	double tmp;

	tmp = a->raydis_door;
	a->raydis_door = b->raydis_door;
	b->raydis_door = tmp;
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

	while (v->door)
	{
		tmp = v->door;
		while (tmp)
		{
			if (v->door->raydis_door < tmp->raydis_door)
				swad_data(v->door, tmp);
			tmp = tmp->next;
		}
		text_door(v);
		v->door = v->door->next;
	}
	v->door = NULL;
}