#include"cub3D.h"


int main()
{
    int i = 0;
    int ang = 270 - 180 - 30;

    while (i <= 60)
    {
        printf("i = %d calcule = %d\n", i, ang + (i));
        i++;
    }
    
}