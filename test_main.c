#include"include/cub3D.h"

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
double	Rad(double angle)
{
	return (angle * (M_PI / 180));
}
void test(char **p)
{
    printf("add = %p  str = %s\n", *p, *p);
    *p = malloc(40);
    *p[0] = 'a';
    *p[1] = '\0';
    printf("add = %p  str = %s\n", *p, *p);
    // return p;
}
int main()
{
    int h;
    int w;
    int bitp;
    int line;
    int end;
    void *mlx = mlx_init();
    void *img =  mlx_xpm_file_to_image(mlx, "/Users/yettabaa/Desktop/cub3D/textures/door/door_44.xpm", &w, &h);

    char *no_buff = mlx_get_data_addr(img, &bitp, &line, &end);
    // str = malloc(10);
    unsigned int c = no_buff[0] << 24 | no_buff[1] << 16 | no_buff[2] << 8 | no_buff[3];
    printf("%u\n", c);
    
}
 