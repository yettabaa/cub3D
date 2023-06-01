/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:39:19 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/01 04:32:47 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_mlx_pixel_put(t_data *v, int x, int y, int color)
{
	char	*dst;

	dst = v->mlx.addr + (y * v->mlx.line_length + x * (v->mlx.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void initialisation(t_data *v)
{
    // v->epsilon = 1e-8; // ??? hit the wall in the origin axis  // (1,5) angle 225
    v->epsilon = 0.01; // ??? hit the wall in the origin axis  // (1,5) angle 225
    v->scal = 40;
    v->orientation = 270;
    v->x = (1 * v->scal + v->scal / 2);
    v->y = (5 * v->scal + v->scal / 2);
    // v->x = (1 * v->scal + v->scal / 2) + (1 * cos(rad(v->orientation)));
    // v->y = (5 * v->scal + v->scal / 2) + (1 * sin(rad(v->orientation)));
}

char **read_maps(char *file)
{
    char **s;
    int fd = open(file, O_RDONLY);
    int size = 1;
    char *buf;
    char *str;

    str = NULL;
    buf = malloc(BUFFER_SIZE + 1);
    while (size > 0)
    {
        size = read(fd, buf, BUFFER_SIZE);
        buf[size] = '\0';
        str = ft_strjoin(str, buf);                    
    }
    s = ft_split(str, '\n');
    return(s);
}

int destroy(void)
{
    exit(0);
    return (0);
}

int	key(int keycode, t_data *v)
{
    // int inc = 3;

    if (keycode == 53)
		exit(0);
    else if (keycode == 123)
		v->orientation -= 1;
	else if (keycode == 124)
		v->orientation += 1;
    else if (keycode == 125)
		v->orientation -= 10;
	else if (keycode == 126)
		v->orientation += 10;
    else if (keycode == 84)   
        v->y += 20; 
    else if (keycode == 91)
        v->y -= 20;
    else if (keycode == 86)
        v->x -= 20;    
    else if (keycode == 88)
        v->x += 20;    
    else if (keycode == W)
        direction(v, W);
    else if (keycode == S)
        direction(v, S);
    else if (keycode == D)
        direction(v, D);
    else if (keycode == A)
        direction(v, A);
    mlx_destroy_image(v->mlx.mlx, v->mlx.img);
	v->mlx.img = mlx_new_image(v->mlx.mlx, WIDTH, HIGHT);
	v->mlx.addr = mlx_get_data_addr(v->mlx.img, &v->mlx.bits_per_pixel, &v->mlx.line_length,
			&v->mlx.endian);
	maps_2d(v);
    // player(v, 0xff);
	mlx_put_image_to_window(v->mlx.mlx, v->mlx.mlx_win, v->mlx.img, 0, 0);
    return(0);
}

int main(int ac ,char **av)
{
	t_data v;
    (void)ac;

	v.mlx.mlx = mlx_init();
	v.mlx.mlx_win = mlx_new_window(v.mlx.mlx, WIDTH, HIGHT, "Hello world!");
	v.mlx.img = mlx_new_image(v.mlx.mlx, WIDTH, HIGHT);
	v.mlx.addr = mlx_get_data_addr(v.mlx.img, &v.mlx.bits_per_pixel, &v.mlx.line_length,
								&v.mlx.endian); 
    v.map = read_maps(av[1]);
    initialisation(&v);
    maps_2d(&v);
	mlx_put_image_to_window(v.mlx.mlx, v.mlx.mlx_win, v.mlx.img, 0, 0);
    mlx_hook(v.mlx.mlx_win, 2, 0, key, &v);
    // mlx_loop_hook(v.mlx.mlx, key, &v);
    mlx_hook(v.mlx.mlx_win, 17, 0, destroy, &v);
	mlx_loop(v.mlx.mlx);
}
