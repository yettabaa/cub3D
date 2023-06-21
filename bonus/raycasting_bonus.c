/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 03:22:31 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/21 01:20:47 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

typedef struct s_norme{
    
    int i;
    int j;
    int iq;
    double smal_sidstp;
    double big_sidstp;
    int txw;
}t_norme;

static void inc_smal_steps(t_data *v,t_object **object, double ang)
{
    t_norme n;

    n.smal_sidstp = v->ryc.DVside;
    n.txw = VER;
    (v->ryc.Vdelta > v->ryc.Hdelta) && (n.smal_sidstp = v->ryc.DHside);
    (v->ryc.Vdelta > v->ryc.Hdelta) && (n.txw = HORI);
    v->ryc.x = v->x + (n.smal_sidstp * cos(Rad(ang)));
    v->ryc.y = v->y + (n.smal_sidstp * sin(Rad(ang)));
    visualize_maps(v, ang, &n.i, &n.j);
    v->ryc.smal_stp = n.smal_sidstp;
    if (check_(v, n.i, n.j, DOOR) ) 
        addobjt(object, newdoor(v, n.smal_sidstp, n.txw));
    n.iq = 1;
    while (check_(v, n.i, n.j, WALL))
    {
        v->ryc.smal_stp = n.iq++ * fmin(v->ryc.Hdelta, v->ryc.Vdelta) + n.smal_sidstp;
        v->ryc.x = v->x + (v->ryc.smal_stp * cos(Rad(ang)));
        v->ryc.y = v->y + (v->ryc.smal_stp * sin(Rad(ang)));
        visualize_maps(v, ang, &n.i, &n.j);
        if (check_(v, n.i, n.j, DOOR)) 
            addobjt(object, newdoor(v, v->ryc.smal_stp, n.txw));
    }
}

static void inc_big_steps(t_data *v,t_object **object, double ang)
{
    t_norme n;
    
    n.big_sidstp = v->ryc.DHside;
    n.txw = HORI;
    (v->ryc.Vdelta > v->ryc.Hdelta) && (n.big_sidstp = v->ryc.DVside);
    (v->ryc.Vdelta > v->ryc.Hdelta) && (n.txw = VER);
    v->ryc.x = v->x + (n.big_sidstp * cos(Rad(ang)));
    v->ryc.y = v->y + (n.big_sidstp * sin(Rad(ang)));
    visualize_maps(v, ang, &n.i, &n.j);
    v->ryc.big_stp = n.big_sidstp;
    if (n.big_sidstp < v->ryc.smal_stp && check_(v, n.i, n.j, DOOR)) 
        addobjt(object, newdoor(v, n.big_sidstp, n.txw));
    n.iq = 1;
    while (n.big_sidstp < v->ryc.smal_stp && check_(v, n.i, n.j, WALL))
    {
        v->ryc.big_stp = n.iq++ * fmax(v->ryc.Hdelta, v->ryc.Vdelta) + n.big_sidstp;
        v->ryc.x = v->x + (v->ryc.big_stp * cos(Rad(ang)));
        v->ryc.y = v->y + (v->ryc.big_stp * sin(Rad(ang)));
        visualize_maps(v, ang, &n.i, &n.j);
        if (v->ryc.big_stp < v->ryc.smal_stp && check_(v, n.i, n.j, DOOR)) 
            addobjt(object, newdoor(v, v->ryc.big_stp, n.txw));
        if (v->ryc.big_stp > v->ryc.smal_stp || check_(v, n.i, n.j, 0))
            break;
    }
}

double raycasting_bonus(t_data *v,t_object **object, double ang)
{
    steps(v, ang);
    inc_smal_steps(v,object,  ang);
    inc_big_steps(v,object, ang);

    v->raydis = fmin(v->ryc.smal_stp, v->ryc.big_stp); // fixing fishbowl
    v->raydis_fishbowl = fmin(v->ryc.smal_stp, v->ryc.big_stp) * cos(Rad(v->orientation - ang)); // fixing fishbowl
    if (v->ryc.big_stp > v->ryc.smal_stp && v->ryc.Hdelta > v->ryc.Vdelta + v->epsilon)
        v->txt.hitWall = VER;
    else if (v->ryc.big_stp < v->ryc.smal_stp && v->ryc.Hdelta + v->epsilon < v->ryc.Vdelta)
        v->txt.hitWall = VER;
    else if (v->ryc.big_stp > v->ryc.smal_stp && v->ryc.Hdelta + v->epsilon < v->ryc.Vdelta)
        v->txt.hitWall = HORI;
    else if (v->ryc.big_stp < v->ryc.smal_stp && v->ryc.Hdelta > v->ryc.Vdelta+ v->epsilon)
        v->txt.hitWall = HORI;
    v->xw = v->x + (v->raydis * cos(Rad(ang))); //translation with distace of adjacent
    v->yw = v->y + (v->raydis * sin(Rad(ang))); //translation with distace of opposite
    addobjt(object, newdoor(v, v->raydis, WALL));
    return(v->raydis);
}