#include"cub3D.h"

double Angle(double x){

    if (x <= 180)
        return x;    
    return x -360 ;
}
int constrainAngle(){
    double x = 5.0000001;
    double y = 5;
    return (x < y);
}
// double constrainAngle(double x){
//     x = fmod(x,360);
//     if (x < 0)
//         x += 360;
//     return x;
// }
int main()
{
    // int i = 0;
    // int ang = 270 - 180 - 30;
    double x = 150;
    double y = 30;
    // printf("ang =  %f\n", Angle(359));
    // printf("cons =  %f\n", constrainAngle(150));
    // printf("cons =  %f\n", x / y);
    printf("cons =  %d\n", constrainAngle());
    // while (i <= 60)
    // {
    //     printf("i = %d calcule = %d\n", i, ang + (i));
    //     i++;
    // }
    
}
 int i;
    int j;
    int iq;

    // puts("----------------");
    if (v->Vdelta < v->Hdelta)
        v->smal_sidstp = v->DVside;
    else
        v->smal_sidstp = v->DHside;
    v->x1 = v->x + (v->smal_sidstp * cos(rad(ang)) + v->error); // (1,5) angle 225
    v->y1 = v->y + (v->smal_sidstp * sin(rad(ang)))+ v->error; 
    j = v->y1 / v->scal;
    i = v->x1 / v->scal;
    printf("(x_p = %f ,y_p = %f) DVside = %f DHside %f\n",v->x,v->y, v->DVside, v->DHside);
    if (i && ang > 90 && ang < 270 && v->DVside < v->DHside) // i  > 0 handline cos NULL
    {
        puts("i--");
        i -= 1;
    }
    if(j && ang > 180 && ang < 360 && v->DVside > v->DHside) 
        j -= 1;
    if ((int)v->map[j][i] == '1' && (int)v->map[(int)(v->y  / v->scal)][(int)((v->x - v->error) / v->scal)] == '1') 
    {
        v->x1 = v->x;
        v->y1 = v->y;
    }
    iq = 1;
    printf("ang = %f v->Smal_sidstp %f  (x = %f, y = %f) (i = %d, j = %d)\n",ang, v->smal_sidstp,v->x1,v->y1,i,j);
    // printf("iq = %d (i = %d iz = %f, j = %d) \n",i,(v->x1 / v->scal),j);
    v->smal_stp = v->smal_sidstp;
    while ((int)v->map[j][i] != '1')
    {
        v->smal_stp = (iq * fmin(v->Hdelta, v->Vdelta) + v->smal_sidstp);
        v->x1 = v->x + (v->smal_stp * cos(rad(ang))) + v->error; //translation with distace of adjacent
        v->y1 = v->y + (v->smal_stp * sin(rad(ang))) + v->error; //translation with distace of opposite        
        i = v->x1 / v->scal;
        j = v->y1 / v->scal;
        if (ang > 90 && ang < 270 && v->Vdelta < v->Hdelta)
            i -= 1;
        if(ang > 180 && ang < 360 && v->Vdelta > v->Hdelta) 
            j -= 1;
        printf("ang %f (Vdelta = %f, Hdelta = %f)  (smal_steps = %f) i == %d, j == %d iq = %d (x = %f, y = %f) \n",ang,v->Vdelta,v->Hdelta, v->smal_stp,i,j,iq, v->x1, v->y1);
        iq++;
    }
    