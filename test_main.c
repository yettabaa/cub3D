#include"cub3D.h"

double Angle(double x){

    if (x <= 180)
        return x;    
    return x -360 ;
}
double constrainAngle(double x){
    x = fmod(x,360);
    if (x < 0)
        x += 360;
    return x;
}
int main()
{
    int i = 0;
    int ang = 270 - 180 - 30;

    printf("ang =  %f\n", Angle(359));
    printf("cons =  %f\n", constrainAngle(150));
    // while (i <= 60)
    // {
    //     printf("i = %d calcule = %d\n", i, ang + (i));
    //     i++;
    // }
    
}