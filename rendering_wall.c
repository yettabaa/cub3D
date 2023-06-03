/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_wall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 00:27:41 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/03 01:22:09 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void rendering_wall(t_data *v)
{
    double disProj = (WIDTH / 2) / tan(rad(30));
    double wall_hight = (v->scal /2 / v->raydis) * disProj;
    v->y0 = ((HIGHT) / 2) - (wall_hight / 2);
    v->y1 = v->y0 + wall_hight;
    dda(v, v->x0, v->y0, v->x0, v->y1, 0xff0000);
    // dda(v,0,100 ,100,30,0xffffff);
}