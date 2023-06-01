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
double	rad(double angle)
{
	return (angle * (M_PI / 180));
}
int main()
{
    // int i = 0;
    // int ang = 270 - 180 - 30;
    double x = 500;
    double y = 30;
    int inc = 10;
    // printf("ang =  %f\n", Angle(359));
    printf("con =  %f\n", (inc - inc / 3) * cos(rad(40)));
    printf("sin =  %f\n\n", (inc - inc / 3) * sin(rad(40)));



    printf("cons =  %f\n", (inc - 3) * cos(rad(40)));
    printf("sin =  %f\n", (inc - 3) * sin(rad(40)));
    // printf("cons =  %f\n", x / y);
    // printf("cons =  %f\n", round(0.45));
    // while (i <= 60)
    // {
    //     printf("i = %d calcule = %d\n", i, ang + (i));
    //     i++;
    // }
    
}
 