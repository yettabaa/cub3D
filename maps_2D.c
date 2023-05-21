/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_2D.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 01:50:02 by yettabaa          #+#    #+#             */
/*   Updated: 2023/05/21 19:25:39 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
double	rad(double degree)
{
	return (degree * (M_PI / 180));
}
void player(t_data *img, int i, int j, int hight)
{
    int x, y;
    int x1, y1;
    int distance = 100;
    int angle = -90;
    
    x = (i * hight) + (hight / 2);
    y = (j * hight) + (hight / 2);
    disc(img, x, y, hight / 5, 0xff0000);
    // x1 = (x + distance) *  cos(rad(angle));
    // y1 = (y + distance) *  sin(rad(angle));
    x1 = x + distance *  cos(rad(angle));
    y1 = y + distance *  sin(rad(angle));
    dda(img, x, y, x1, y1, 0xff0000);
    
}

// void ray()

void maps_2d(t_data *img, char **map)
{
    int i;
    int j;
    int x = 0;
    int y = 0;
    int hight = 30;
    
    j = -1;
    while (map[++j])
    {
        i = -1;
        x = 0;
        while (map[j][++i])
        {
            // printf("i = %d\n", i);
            if ((int)map[j][i] == '1')
                rectangle(img, x, y, hight, hight, 0xff);
            else if ((int)map[j][i] == '0')
                rectangle(img, x, y, hight, hight, 0xffffff);
            else if ((int)map[j][i] == 32)
                rectangle(img, x, y, hight, hight, 0);
            else
            {
                rectangle(img, x, y, hight, hight, 0xffffff);
                player(img, i, j, hight);
            }
            x += hight;        
        }
        y += hight;
    }
    j = -1;
    while (map[++j])
    {
        i = -1;
        while (map[j][++i])
        {
            dda(img, i * hight, j * hight, (i + 1) * hight, j * hight, 0);
            dda(img, i * hight, j * hight, i * hight, (j + 1) * hight, 0);
        }
    }
}