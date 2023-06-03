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
   double i = 310.01;
   double j = 30;
    printf("%f\n", ceil(i));
    
    
}
 