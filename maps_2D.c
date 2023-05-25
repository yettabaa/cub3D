/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_2D.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 01:50:02 by yettabaa          #+#    #+#             */
/*   Updated: 2023/05/26 00:14:02 by yettabaa         ###   ########.fr       */
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
void steps(t_data *v, double ang)
{
    int var;
    
    var = (int)(v->y / v->scal);
    v->y_H1stp = (v->y - (var * v->scal)); // up
    (ang > 0 && ang < 180) && (v->y_H1stp = ((var * v->scal + v->scal) - v->y)); // down
    v->x_H1stp = 0;
    (ang != 0 && ang != 180) && (v->x_H1stp = v->y_H1stp / tan(rad(ang)));
    v->DHside = sqrt(pow(v->x_H1stp, 2) + pow(v->y_H1stp, 2));
    printf("dx = %f dy = %f ipo = %f\n", v->x_H1stp, v->y_H1stp, v->DHside);
    
    v->y_Hstp = v->scal;
    v->x_Hstp = 0;
    (ang != 0 && ang != 180) &&  (v->x_Hstp = v->scal / tan(rad(ang))); //tan +/-
    v->Hdelta = sqrt(pow(v->x_Hstp, 2) + pow(v->y_Hstp, 2));
    // printf("x_H1stp = %f y_H1stp = %f x_Hstp = %f y_Hstp = %f tan = %f\n", v->x_H1stp, v->y_H1stp,v->x_Hstp,v->x_Hstp, tan(rad(angof_vue)));
    // printf("\nv->x = %f\n", (v->x_V1stp * v->scal + v->scal - v->x));
    
    
    var = (v->x / v->scal); // can be in a varible // can initialized
    v->x_V1stp = v->x - var * v->scal; // left
    if ((ang > 270 && ang < 360) || (ang > 0 && ang < 90)) // x++ / x-- //right
        v->x_V1stp = (var * v->scal + v->scal) - v->x;
    (ang == 270 || ang == 90) && (v->x_V1stp = 0);    
    v->y_V1stp = v->x_V1stp * tan(rad((ang)));
    v->DVside = sqrt(fabs(pow(v->x_V1stp , 2)) + fabs(pow(v->y_V1stp, 2)));

    v->x_Vstp = v->scal;
    (ang == 0) && (v->y_Vstp = 0);
    v->y_Vstp = v->scal * tan(rad(normalize_angle_180(ang))); // tan vari +/-
    v->Vdelta = sqrt(pow(v->x_Vstp, 2) + pow(v->y_Vstp, 2));
    // printf("dx = %f dy = %f ipo = %f\n", v->x_V1stp, v->y_V1stp, v->DVside);
}

int horisontal_intersections(t_data *v, double ang)
{
    int i;
    int j;
    double erreur = 0.000001; // ??? hit the wall in the origin axis 

    v->x1 = v->x + (fmin(v->DHside, v->DVside) * cos(rad(ang))); //translation with distace of adjacent
    v->y1 = v->y + (fmin(v->DHside, v->DVside) * sin(rad(ang))); //translation with distace of opposite
    i = v->x1 / v->scal;
    (v->DHside > v->DVside && ang > 90 && ang < 270) && (i -= 1); // left // ?
    j = v->y1 / v->scal;
    (v->DHside < v->DVside && ang > 180 && ang < 360) && (j -= 1); // up
    // printf("ang = %f h = %f v = %f        i = %d  ,  j = %d\n",ang, v->DHside, v->DVside,i,j);
    // if ((int)v->map[j][i] != '1')
    // {
    //     v->x1 = v->x + (fmax(v->DHside, v->DVside) * cos(rad(ang))); //translation with distace of adjacent
    //     v->y1 = v->y + (fmax(v->DHside, v->DVside) * sin(rad(ang))); //translation with distace of opposite
    //     i = v->x1 / v->scal;
    //     (v->DHside < v->DVside&& ang > 90 && ang < 270) && (i -= 1); // left
    //     j = v->y1 / v->scal;
    //     (v->DHside < v->DVside && ang > 180 && ang < 360) && (j -= 1); // up
    // }
    
        
    // double tx;
    // double ty;
    puts("----------------");
    int iq = 1;
    double smal_steps;
    //     printf("iq = %d (i = %d iz = %f, j = %d) ang = %f cos = %f sin %f\n", iq++, i,(v->x1 / v->scal),j,ang, v->Hdelta * cos(rad(ang)), v->Hdelta * sin(rad(ang)));
    while ((int)v->map[j][i] != '1')
    {
        smal_steps = (iq * fmin(v->Hdelta, v->Vdelta) + fmin(v->DHside, v->DVside));
        v->x1 = v->x + (smal_steps * cos(rad(ang))) + erreur; //translation with distace of adjacent
        v->y1 = v->y + (smal_steps * sin(rad(ang))) + erreur; //translation with distace of opposite
        i = v->x1 / v->scal;
        (v->DHside > v->DVside && ang > 90 && ang < 270) && (i -= 1); // left // ?
        j = v->y1 / v->scal;
        (v->DHside < v->DVside && ang > 180 && ang < 360) && (j -= 1); // up
        iq++;
    }
    
    int iqtale3 = 1;
    double big_steps;
    // if ( (int)v->map[j][i] == '1' && fmax(v->Hdelta, v->Vdelta) < smal_steps )
    // {
    v->x1 = v->x + (fmax(v->DHside, v->DVside) * cos(rad(ang))); //translation with distace of adjacent
    v->y1 = v->y + (fmax(v->DHside, v->DVside) * sin(rad(ang))); //translation with distace of opposite
    i = v->x1 / v->scal;
    // (v->DHside > v->DVside && ang > 90 && ang < 270) && (i -= 1); // left // ?
    j = v->y1 / v->scal;
    (v->DHside < v->DVside && ang > 180 && ang < 360) && (j -= 1); // up
    printf("1- ang %f (Vdelta = %f, Hdelta = %f)  (smal_steps = %f) i == %d, j == %d iq = %d iqzab %d\n",ang,v->Vdelta,v->Hdelta, smal_steps,i,j,iq,iqtale3);
    while ((int)v->map[j][i] != '1')
    {
        big_steps = (iqtale3 * fmax(v->Hdelta, v->Vdelta) + fmax(v->DHside, v->DVside));
        v->x1 = v->x + (big_steps * cos(rad(ang))) + erreur; //translation with distace of adjacent
        v->y1 = v->y + (big_steps * sin(rad(ang))) + erreur; //translation with distace of opposite
        i = v->x1 / v->scal;
        (v->DHside < v->DVside && ang > 90 && ang < 270) && (i -= 1); // left // ?
        j = v->y1 / v->scal;
        (v->DHside > v->DVside && ang > 180 && ang < 360) && (j -= 1); // up
        iqtale3++;
        printf("1- ang %f (Vdelta = %f, Hdelta = %f)  (smal_steps = %f, big_steps = %f) i == %d, j == %d iq = %d iqzab %d\n",ang,v->Vdelta,v->Hdelta, smal_steps, big_steps,i,j,iq,iqtale3);
        if (big_steps > smal_steps || (int)v->map[j][i] == '1')
        {
            puts("ss");
            break;
        }
    }
    v->x1 = v->x + (fmin(smal_steps,big_steps) * cos(rad(ang))) + erreur; //translation with distace of adjacent
    v->y1 = v->y + (fmin(smal_steps,big_steps) * sin(rad(ang))) + erreur; //translation with distace of opposite
    i = v->x1 / v->scal;
    (v->DHside < v->DVside && ang > 90 && ang < 270) && (i -= 1); // left // ?
    j = v->y1 / v->scal;
    (v->DHside > v->DVside && ang > 180 && ang < 360) && (j -= 1); // up
    // }
        // printf("ang %f   i == %d, j == %d iq = %d iqzab %d\n",ang,i,j,iq,iqtale3);
        // v->x1 += (v->Hdelta * cos(rad(ang))) + erreur; //translation with distace of adjacent
        // v->y1 += (v->Hdelta * sin(rad(ang))) + erreur; //translation with distace of opposite
        // i = v->x1 / v->scal;
        // j = v->y1 / v->scal;
        // (ang > 180 && ang < 360) && (j -= 1); // up
    return 0;
}
// int horisontal_intersections(t_data *v, double ang)
// {
//     int i;
//     int j;
//     double erreur = 0.0001; // ??? hit the wall in the origin axis 

//     v->x1 = v->x + (v->DHside * cos(rad(ang))); //translation with distace of adjacent
//     v->y1 = v->y + (v->DHside * sin(rad(ang))); //translation with distace of opposite
//     i = v->x1 / v->scal;
//     j = v->y1 / v->scal;
//     (ang > 180 && ang < 360) && (j -= 1); // up
//     puts("----------------");
//     int iq = 0;
//     while (i >= 0 && j >= 0 && v->map[j][i] && (int)v->map[j][i] != '1')
//     {
//         v->x1 += (v->Hdelta * cos(rad(ang))) + erreur; //translation with distace of adjacent
//         v->y1 += (v->Hdelta * sin(rad(ang))) + erreur; //translation with distace of opposite
//         i = v->x1 / v->scal;
//         j = v->y1 / v->scal;
//         (ang > 180 && ang < 360) && (j -= 1); // up
//         printf("iq = %d (i = %d iz = %f, j = %d) ang = %f cos = %f sin %f\n", iq++, i,(v->x1 / v->scal),j,ang, v->Hdelta * cos(rad(ang)), v->Hdelta * sin(rad(ang)));
//     }
//     return 0;
// }

void vertical_intersections(t_data *v, double ang)
{
    int i;
    int j;
    double erreur = 0.001; // ???

    v->x1 = v->x + (v->DVside * cos(rad(ang))); //translation with distace of adjacent
    v->y1 = v->y + (v->DVside * sin(rad(ang))); //translation with distace of opposite
    j = v->y1 / v->scal;
    i = v->x1 / v->scal;
    (ang > 90 && ang <= 270) && (i -= 1); // left
    // puts("----------------");
    // int iq = 0;
    while ((int)v->map[j][i] != '1')
    {
        v->x1 += (v->Vdelta * cos(rad(ang))) + erreur; //translation with distace of adjacent
        v->y1 += (v->Vdelta * sin(rad(ang))) + erreur; //translation with distace of opposite
        j = v->y1 / v->scal;
        i = v->x1 / v->scal;
        (ang > 90 && ang < 270) && (i -= 1); // left
        // printf("iq = %d (i = %d iz = %f, j = %d) ang = %f cos = %f sin %f\n", iq++, i,(v->x1 / v->scal),j,ang, v->Vdelta * cos(rad(ang)), v->Vdelta * sin(rad(ang)));
    }
}

void player(t_data *v, int color)
{
    int frequency = 0;
    int vi = 0;
    int ang;
    
    disc(v, color);
    // puts("---------------"); 
    ang = normalize_angle_360(v->angle - 30);
    while (vi <= frequency)
    {
        // puts("---------------------------------\n");
        // printf("dda ==> (x = %f, y = %f) - (xf = %f, yf = %f\n", v->x, v->y, v->x_first, v->y_first);
        
        // if (vi == 0 || vi == 60)
        // {
            steps(v, normalize_angle_360(ang + vi));
            horisontal_intersections(v, normalize_angle_360(ang + vi));
                // break;
            // vertical_intersections(v, normalize_angle_360(ang + vi));
            dda(v, v->x, v->y, v->x1, v->y1, color);
            // printf("vi = %d ang  = %dng\n", vi, ang +vi);
        // }
        vi++;
        // break;
    }
    // dda(v,0,100 ,100,30,0xffffff);
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
