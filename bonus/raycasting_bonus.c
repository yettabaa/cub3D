/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 03:22:31 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/16 05:06:54 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void inc_smal_steps(t_data *v, double ang)
{
    int i;
    int j;
    int iq;
    double smal_sidstp;
    int txw;

    
    smal_sidstp = v->ryc.DVside;
    txw = VER;
    if (v->ryc.Vdelta > v->ryc.Hdelta)
    {
        smal_sidstp = v->ryc.DHside;
        txw = HORI;
    }
    // (v->ryc.Vdelta <= v->ryc.Hdelta) && (smal_sidstp = v->ryc.DVside);
    // (v->ryc.Vdelta > v->ryc.Hdelta) && (smal_sidstp = v->ryc.DHside);
    v->ryc.x = v->x + (smal_sidstp * cos(rad(ang)));
    v->ryc.y = v->y + (smal_sidstp * sin(rad(ang)));
    visualize_maps(v, ang, &i, &j);
    v->ryc.smal_stp = smal_sidstp;
    if ((int)v->pars.map[j][i] == '2') 
        addoor(&v->list_door, newdoor(v, smal_sidstp, txw));
    iq = 1;
    while ((int)v->pars.map[j][i] != '1')
    {
        v->ryc.smal_stp = iq++ * fmin(v->ryc.Hdelta, v->ryc.Vdelta) + smal_sidstp;
        v->ryc.x = v->x + (v->ryc.smal_stp * cos(rad(ang)));
        v->ryc.y = v->y + (v->ryc.smal_stp * sin(rad(ang)));
        visualize_maps(v, ang, &i, &j);
        if ((int)v->pars.map[j][i] == '2') 
            addoor(&v->list_door, newdoor(v, v->ryc.smal_stp, txw));
    }
}

void inc_big_steps(t_data *v, double ang)
{
    int i;
    int j;
    int iq;
    double big_sidstp;
    int txw;
    
    big_sidstp = v->ryc.DHside;
    txw = HORI;
    if (v->ryc.Vdelta > v->ryc.Hdelta)
    {
        (big_sidstp = v->ryc.DVside);
        txw = VER;
    }
    // (v->ryc.Vdelta <= v->ryc.Hdelta) && (big_sidstp = v->ryc.DHside);
    // (v->ryc.Vdelta > v->ryc.Hdelta) && (big_sidstp = v->ryc.DVside);
    v->ryc.x = v->x + (big_sidstp * cos(rad(ang)));
    v->ryc.y = v->y + (big_sidstp * sin(rad(ang)));
    visualize_maps(v, ang, &i, &j);
    v->ryc.big_stp = big_sidstp;
    if (big_sidstp < v->ryc.smal_stp && (int)v->pars.map[j][i] == '2') 
        addoor(&v->list_door, newdoor(v, big_sidstp, txw));
    iq = 1;
    while (big_sidstp < v->ryc.smal_stp && (int)v->pars.map[j][i] != '1')
    {
        v->ryc.big_stp = iq++ * fmax(v->ryc.Hdelta, v->ryc.Vdelta) + big_sidstp;
        v->ryc.x = v->x + (v->ryc.big_stp * cos(rad(ang)));
        v->ryc.y = v->y + (v->ryc.big_stp * sin(rad(ang)));
        visualize_maps(v, ang, &i, &j);
        if (v->ryc.big_stp < v->ryc.smal_stp && (int)v->pars.map[j][i] == '2') 
            addoor(&v->list_door, newdoor(v, v->ryc.big_stp, txw));
        if (v->ryc.big_stp > v->ryc.smal_stp || (int)v->pars.map[j][i] == '1')
            break;
    }
}

double raycasting_bonus(t_data *v, double ang)
{
    steps(v, ang);
    inc_smal_steps(v, ang);
    inc_big_steps(v, ang);
    // printf("(DVside = %f, DHside = %f)\n",v->ryc.DVside,v->ryc.DHside);
    // printf("(Vdelta = %f, Hdelta = %f)\n",v->ryc.Vdelta,v->ryc.Hdelta);
    // printf("big %f small %f\n", v->ryc.big_stp, v->ryc.smal_stp);
    v->raydis = fmin(v->ryc.smal_stp, v->ryc.big_stp); // fixing fishbowl
    v->raydis_fishbowl = fmin(v->ryc.smal_stp, v->ryc.big_stp) * cos(rad(v->orientation - ang)); // fixing fishbowl
    if (v->ryc.big_stp > v->ryc.smal_stp && v->ryc.Hdelta > v->ryc.Vdelta + v->epsilon)
        v->txt.hitWall = VER;
    else if (v->ryc.big_stp < v->ryc.smal_stp && v->ryc.Hdelta + v->epsilon < v->ryc.Vdelta)
        v->txt.hitWall = VER;
    else if (v->ryc.big_stp > v->ryc.smal_stp && v->ryc.Hdelta + v->epsilon < v->ryc.Vdelta)
        v->txt.hitWall = HORI;
    else if (v->ryc.big_stp < v->ryc.smal_stp && v->ryc.Hdelta > v->ryc.Vdelta+ v->epsilon)
        v->txt.hitWall = HORI;
    v->xw = v->x + (v->raydis * cos(rad(ang))); //translation with distace of adjacent
    v->yw = v->y + (v->raydis * sin(rad(ang))); //translation with distace of opposite
    addoor(&v->list_door, newdoor(v, v->raydis, WALL));
    return(v->raydis);
}