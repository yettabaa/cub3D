/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_2D.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 01:50:02 by yettabaa          #+#    #+#             */
/*   Updated: 2023/05/24 20:17:24 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
typedef double t_deg;
typedef double t_rad;

t_rad	rad(t_deg angle)
{
	return (angle * (M_PI / 180));
}
double normalize_angle_180(double x){
    // int tmp = x;

    // if (x <= 180)
    //     return x;
    // x = fmod(x + 180,360);
    // if (x < 0)
    //     x += 360;
    // (tmp > 180) && (x *= -1);    
    // return x ;
    if (x <= 180)
        return x;    
    return x -360 ;
}
double normalize_angle_360(double x){
    x = fmod(x,360);
    if (x < 0)
        x += 360;
    return x;
}
void steps(t_data *v, double angof_vue)
{
    v->y_H1stp = (int)(v->y / v->scal);
    v->x_H1stp = 0;
    (angof_vue > 180) && (v->x_H1stp = (v->y - (v->y_H1stp * v->scal)) / tan(rad(angof_vue)));
    (angof_vue < 180) && (v->x_H1stp = ((v->y_H1stp * v->scal + v->scal) - v->y) / tan(rad(angof_vue)));
    
    v->y_Hstp = v->scal;
    v->x_Hstp = 0;
    (angof_vue < 90) && (v->x_Hstp = v->scal / tan(rad(angof_vue)));
    (angof_vue > 90) && (v->x_Hstp = -1 * v->scal / tan(rad(180 - angof_vue))); //???
    // printf("x_H1stp = %f y_H1stp = %f x_Hstp = %f y_Hstp = %f tan = %f\n", v->x_H1stp, v->y_H1stp,v->x_Hstp,v->x_Hstp, tan(rad(angof_vue)));
    v->y_V1stp = 0;
    // printf("\nv->x = %f\n", (v->x_V1stp * v->scal + v->scal - v->x));
    
    v->x_V1stp = (int)(v->x / v->scal);
    if (angof_vue > 0 && angof_vue < 180)
        v->y_V1stp = fabs(((v->x_V1stp * v->scal + v->scal) - v->x)) * tan(rad(angof_vue));
    else    
        v->y_V1stp = fabs((v->x - (v->x_V1stp * v->scal))) * tan(rad(angof_vue));
        
    v->x_Vstp = v->scal;
    (angof_vue == 0) && (v->y_Vstp = 0);
    // if (angof_vue > 0 && angof_vue < 180)
        v->y_Vstp = v->scal * tan(rad(normalize_angle_180(angof_vue))); // tan vari +/-
    // else    
        // v->y_Vstp =  -1 * v->scal * tan(rad(normalize_angle_180(angof_vue)));
    // (angof_vue > 0 && angof_vue < 180) && (v->y_Vstp = v->scal * tan(rad(angof_vue)));
    // (angof_vue < 0) && (v->y_Vstp =  -1 * v->scal * tan(rad(angof_vue)));
    // printf("x_V1stp = %f y_V1stp = %f x_Vstp = %f y_Vstp = %f tan = %f\n", v->x_V1stp, v->y_V1stp,v->x_Vstp,v->x_Vstp, tan(rad(angof_vue)));
}

void vertical_intersections(t_data *v, double angof_vue)
{
    int i;
    int j;
    (void)angof_vue;

    v->x_first = v->x_V1stp * v->scal;
    if ((angof_vue < 270 && angof_vue >= 360) || (angof_vue > 0 && angof_vue < 90))
        v->x_first = v->x_V1stp * v->scal + v->scal;
    if (angof_vue > 0 && angof_vue < 180)   //tan -/+ 
        v->y_first = v->y + v->y_V1stp;
    else
        v->y_first = v->y - v->y_V1stp;
        
    i = v->x_first  / v->scal;
    (angof_vue > 90 && angof_vue <= 270) && (i = (v->x_first  / v->scal) - 1);
    j = v->y_first  / v->scal;
    while ((int)v->map[j][i] != '1')
    {
        if ((angof_vue > 270 && angof_vue < 360) || (angof_vue >= 0 && angof_vue < 90))
            v->x_first += v->x_Vstp;
        else
            v->x_first -= v->x_Vstp;
            
        v->y_first += v->y_Vstp;

        i = v->x_first / v->scal;
        (angof_vue > 90 && angof_vue <= 270) && (i -= 1);
        j = v->y_first  / v->scal;
    }
    
}
void horisontal_intersections(t_data *v, double angof_vue)
{
    int i;
    int j;

    (angof_vue > 180) && (v->y_first = v->y_H1stp * v->scal);
    (angof_vue < 180) && (v->y_first = v->y_H1stp * v->scal + v->scal);
    v->x_first = v->x + v->x_H1stp;
    i = v->x_first  / v->scal;
    (angof_vue > 180) && (j = v->y_first  / v->scal - 1);
    (angof_vue < 180) && (j = v->y_first  / v->scal);
    while ((int)v->map[j][i] != '1')
    {
        v->x_first += v->x_Hstp;
        (angof_vue > 180) && (v->y_first -= v->y_Hstp);
        (angof_vue < 180) && (v->y_first += v->y_Hstp);
        i = v->x_first / v->scal;
        (angof_vue > 180) && (j = v->y_first  / v->scal - 1);
        (angof_vue < 180) && (j = v->y_first  / v->scal);
    }
}

void player(t_data *v, int color)
{
    // int x1;
    // int y1;
    // int distance = 100;
    int frequency = 60;
    int vi = 0;
    int ang;
    
    disc(v, color);
    ang = normalize_angle_360(v->angle - 30);
    while (vi <= frequency)
    {
        // x1 = v->x + (distance * cos(rad(ang + vi))); //translation with distace of adjacent
        // y1 = v->y + (distance * sin(rad(ang + vi++))); //translation with distace of opposite
        // dda(v, v->x, v->y, x1, y1, color);
        printf("(ang = %d, vi = %d) ang/360 = %f ang/180 %f\n", ang, vi, normalize_angle_360(ang+vi),normalize_angle_180(ang + vi));
        steps(v, normalize_angle_360(ang + vi));
        // horisontal_intersections(v, normalize_angle_180(normalize_angle_360(ang + vi)));
        vertical_intersections(v, normalize_angle_360(ang + vi));
        printf("dda ==> (x = %f, y = %f) - (xf = %f, yf = %f\n", v->x, v->y, v->x_first, v->y_first);
        puts("---------------------------------");
        dda(v, v->x, v->y, v->x_first, v->y_first, color);
        vi++;
        // break;
    }
}

void maps_2d(t_data *v)
{
    int i;
    int j;
    
    j = -1;
    while (v->map[++j])
    {
        i = -1;
        while (v->map[j][++i])
        {
            if ((int)v->map[j][i] == '1')
                rectangle(v, i * v->scal, j * v->scal, 0xff);
            else if ((int)v->map[j][i] == 32)
                rectangle(v, i * v->scal, j * v->scal, 0);
            else
                rectangle(v, i * v->scal, j * v->scal, 0xffffff);
            dda(v, i * v->scal, j * v->scal, (i + 1) * v->scal, j * v->scal, 0);
            dda(v, i * v->scal, j * v->scal, i * v->scal, (j + 1) * v->scal, 0);      
        } 
    }
    player(v, 0xff0000);
}