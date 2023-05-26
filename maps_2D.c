/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_2D.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 01:50:02 by yettabaa          #+#    #+#             */
/*   Updated: 2023/05/26 23:47:08 by yettabaa         ###   ########.fr       */
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
    // int v->var;
    v->y_Hstp = v->scal;
    v->x_Hstp = 0;
    (ang != 0 && ang != 180) &&  (v->x_Hstp = v->scal / tan(rad(ang))); //tan +/-
    v->Hdelta = sqrt(pow(v->x_Hstp, 2) + pow(v->y_Hstp, 2));
    
    
    // puts("----------------");
    // printf("ang = %f  (x = %f, y = %f)\n", ang , v->x, v->y);
    v->var = (int)(v->y / v->scal);
    v->y_H1stp = (v->y - (v->var * v->scal)); // up
    ((ang > 0 && ang < 180) || !v->y_H1stp) && (v->y_H1stp = ((v->var * v->scal + v->scal) - v->y)); // down
    v->x_H1stp = 0;
    (ang != 0 && ang != 180) && (v->x_H1stp = v->y_H1stp / tan(rad(ang)));
    v->DHside = sqrt(pow(v->x_H1stp, 2) + pow(v->y_H1stp, 2));
    // printf("ang = %f dx = %f dy = %f ipo = %f\n",ang, v->x_H1stp, v->y_H1stp, v->DHside);
    
    // printf("x_H1stp = %f y_H1stp = %f x_Hstp = %f y_Hstp = %f\n", v->x_H1stp, v->y_H1stp,v->x_Hstp,v->x_Hstp);
    // printf("\nv->x = %f\n", (v->x_V1stp * v->scal + v->scal - v->x));
    
    
    v->x_Vstp = v->scal;
    (ang == 0) && (v->y_Vstp = 0);
    v->y_Vstp = v->scal * tan(rad(normalize_angle_180(ang))); // tan vari +/-
    v->Vdelta = sqrt(pow(v->x_Vstp, 2) + pow(v->y_Vstp, 2));
    
    
    v->var = (v->x / v->scal); // can be in a varible // can initialized
    v->x_V1stp = v->x - v->var * v->scal; // left
    if (((ang > 270 && ang < 360) || (ang > 0 && ang < 90)) || !v->x_V1stp) // x++ / x-- //right
        v->x_V1stp = (v->var * v->scal + v->scal) - v->x;
    (ang == 270 || ang == 90) && (v->x_V1stp = 0);    
    v->y_V1stp = v->x_V1stp * tan(rad((ang)));
    v->DVside = sqrt(fabs(pow(v->x_V1stp , 2)) + fabs(pow(v->y_V1stp, 2)));

    // printf("x_V1stp = %f y_V1stp = %f x_Vstp = %f y_Vstp = %f\n", v->x_V1stp, v->y_V1stp,v->x_Vstp,v->x_Vstp);
    // printf("dx = %f dy = %f ipo = %f\n", v->x_V1stp, v->y_V1stp, v->DVside);
}

int horisontal_intersections(t_data *v, double ang)
{
    int i;
    int j;
    int iq;
    double erreur = 0.000001; // ??? hit the wall in the origin axis
    double smal_sidstp;
    double smal_stp;
    // puts("----------------");
    if (v->Vdelta < v->Hdelta)
        smal_sidstp = v->DVside;
    else
        smal_sidstp = v->DHside;
    v->x1 = v->x + (smal_sidstp * cos(rad(ang))); //translation with distace of adjacent
    v->y1 = v->y + (smal_sidstp * sin(rad(ang))); //translation with distace of opposite
    // if ((ang > 90 && ang < 270))
    //     v->x1 = v->x;
    // if (ang > 180 && ang < 360)
    //     v->y1 = v->y;
    j = v->y1 / v->scal;
    i = v->x1 / v->scal;
    // if ((ang > 90 && ang < 270))
    // {
    //     puts("i--");
    //     i -= 1;
    // }
    // else if (ang > 180 && ang < 360)
    // {
    //     puts("j--");
    //     j -= 1;
    // }
    // printf("DVside = %f DHside %f\n", v->DVside, v->DHside);
    // printf("Smal_sidstp %f  (x = %f, y = %f) (i = %d, j = %d)\n", smal_sidstp,v->x1,v->y1,i,j);
    //     printf("iq = %d (i = %d iz = %f, j = %d) ang = %f cos = %f sin %f\n", iq++, i,(v->x1 / v->scal),j,ang, v->Hdelta * cos(rad(ang)), v->Hdelta * sin(rad(ang)));
    iq = 1;
    smal_stp = smal_sidstp;
    while ((int)v->map[j][i] != '1')
    {
        smal_stp = (iq * fmin(v->Hdelta, v->Vdelta) + smal_sidstp);
        v->x1 = v->x + (smal_stp * cos(rad(ang))) + erreur; //translation with distace of adjacent
        v->y1 = v->y + (smal_stp * sin(rad(ang))) + erreur; //translation with distace of opposite
        // if ((ang > 90 && ang < 270))
        //     v->x1 -= fmin(v->Hdelta, v->Vdelta);
        // if (ang > 180 && ang < 360)
        //     v->y1 -= fmin(v->Hdelta, v->Vdelta);
        
        i = v->x1 / v->scal;
        j = v->y1 / v->scal;
        if (ang > 90 && ang < 270)
        {
            // puts("i--");
            if (ang > 90 && ang < 180 && v->Vdelta < v->Hdelta)
                i -= 1;
            else if (v->Vdelta < v->Hdelta)
                i -= 1;
        }
        if (ang > 180 && ang < 360)
        {
            // puts("j--");
            if (ang > 270 && ang < 360 && v->Vdelta > v->Hdelta)
                j -= 1;
            else if(v->Vdelta > v->Hdelta) 
                j -= 1;
        }
        // printf("ang %f (Vdelta = %f, Hdelta = %f)  (smal_steps = %f) i == %d, j == %d iq = %d (x = %f, y = %f) \n",ang,v->Vdelta,v->Hdelta, smal_stp,i,j,iq, v->x1, v->y1);
        iq++;
    }
    


    double big_sidstp;
    double big_stp;
    
    if (v->Vdelta < v->Hdelta)
        big_sidstp = v->DHside;
    else
        big_sidstp = v->DVside;
    v->x1 = v->x + (big_sidstp * cos(rad(ang))); //translation with distace of adjacent
    v->y1 = v->y + (big_sidstp * sin(rad(ang))); //translation with distace of opposite
    i = v->x1 / v->scal;
    // if (!((ang > 270 && ang < 360) || (ang > 0 && ang < 90)))
            // i -= 1;
    j = v->y1 / v->scal;
    // if (!(ang > 0 && ang < 180))
            // j -= 1;
    // printf("1- ang %f (Vdelta = %f, Hdelta = %f)  (smal_steps = %f) i == %d, j == %d iq = %d iqzab %d\n",ang,v->Vdelta,v->Hdelta, smal_steps,i,j,iq,iq);
    iq = 1;
    big_stp = big_sidstp;
    while (big_sidstp < smal_stp && (int)v->map[j][i] != '1')
    {
        big_stp = (iq * fmax(v->Hdelta, v->Vdelta) + big_sidstp);
        v->x1 = v->x + (big_stp * cos(rad(ang))) + erreur; //translation with distace of adjacent
        v->y1 = v->y + (big_stp * sin(rad(ang))) + erreur; //translation with distace of opposite
        i = v->x1 / v->scal;
        j = v->y1 / v->scal;
        if (ang > 90 && ang < 270)
        {
            // puts("big i--");
            if (ang > 90 && ang < 180 && v->Vdelta > v->Hdelta)
                i -= 1;
            else if (v->Vdelta > v->Hdelta)
                i -= 1;
        }
        if (ang > 180 && ang < 360)
        {
            // puts("big j--");
            if (ang > 270 && ang < 360 && v->Vdelta < v->Hdelta)
                j -= 1;
            else if(v->Vdelta < v->Hdelta) 
                j -= 1;
        }
        iq++;
        // printf("ang %f (Vdelta = %f, Hdelta = %f)  (smal_steps = %f) i == %d, j == %d iq = %d (x = %f, y = %f) \n",ang,v->Vdelta,v->Hdelta, smal_stp,i,j,iq, v->x1, v->y1);
        // printf("2-ang %f (Vdelta = %f, Hdelta = %f)  (smal_steps = %f, big_steps = %f) i == %d, j == %d iq = %d iqzab %d\n",ang,v->Vdelta,v->Hdelta, smal_steps, big_steps,i,j,iq,iqtale3);
        if (big_stp > smal_stp || (int)v->map[j][i] == '1')
            break;
    }
    // printf("3- ang %f (Vdelta = %f, Hdelta = %f)  (smal_steps = %f, big_steps = %f) i == %d, j == %d iq = %d iqzab %d\n",ang,v->Vdelta,v->Hdelta, smal_steps, big_steps,i,j,iq,iqtale3);
    v->x1 = v->x + (fmin(smal_stp,big_stp) * cos(rad(ang))) + erreur; //translation with distace of adjacent
    v->y1 = v->y + (fmin(smal_stp,big_stp) * sin(rad(ang))) + erreur; //translation with distace of opposite
    
    
    return 0;
}

void player(t_data *v, int color)
{
    double frequency = 60;
    double vi = 0;
    double ang;
    
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
            printf("vi = %f ang  = %fng\n", vi, ang +vi);
        // }
        vi += 0.1;
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
                rectangle(v, i * v->scal, j * v->scal, 0x0fff00ff);
            else if ((int)v->map[j][i] == 32)
                rectangle(v, i * v->scal, j * v->scal, 0);
            else
                rectangle(v, i * v->scal, j * v->scal, 0xffffff);
            dda(v, i * v->scal, j * v->scal, (i + 1) * v->scal, j * v->scal, 0);
            dda(v, i * v->scal, j * v->scal, i * v->scal, (j + 1) * v->scal, 0);      
        } 
    }
    player(v, 0xff);
}
