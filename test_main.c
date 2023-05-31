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
double const_Angle(double x){
    x = fmod(x,360);
    if (x < 0)
        x += 360;
    return x;
}
int main()
{
    // int i = 0;
    // int ang = 270 - 180 - 30;
    double x = 500;
    double y = 30;
    // printf("ang =  %f\n", Angle(359));
    printf("cons =  %f\n", const_Angle(x));
    // printf("cons =  %f\n", x / y);
    // printf("cons =  %f\n", round(0.45));
    // while (i <= 60)
    // {
    //     printf("i = %d calcule = %d\n", i, ang + (i));
    //     i++;
    // }
    
}
 