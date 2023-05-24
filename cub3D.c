/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:39:19 by yettabaa          #+#    #+#             */
/*   Updated: 2023/05/24 20:11:47 by yettabaa         ###   ########.fr       */
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
    v->scal = 30;
    v->x = 5 * v->scal + v->scal / 2;
    v->y = 5 * v->scal + v->scal / 2;
    v->angle = 180;
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
    if (keycode == 53)
		exit(0);
    else if (keycode == 123)
		v->angle += 2;
	else if (keycode == 124)
		v->angle -= 2;
    else if (keycode == 0)
        v->x -= 10;
    else if (keycode == 2)
        v->x += 10;
    else if (keycode == 13)
        v->y -= 10;
    else if (keycode == 1)
        v->y += 10;
    mlx_destroy_image(v->mlx.mlx, v->mlx.img);
	v->mlx.img = mlx_new_image(v->mlx.mlx, 1920, 1080);
	v->mlx.addr = mlx_get_data_addr(v->mlx.img, &v->mlx.bits_per_pixel, &v->mlx.line_length,
			&v->mlx.endian);
	maps_2d(v);
	mlx_put_image_to_window(v->mlx.mlx, v->mlx.mlx_win, v->mlx.img, 0, 0);
    return(0);
}

int main(int ac ,char **av)
{
	t_data v;
    (void)ac;

	v.mlx.mlx = mlx_init();
	v.mlx.mlx_win = mlx_new_window(v.mlx.mlx, 1920, 1080, "Hello world!");
	v.mlx.img = mlx_new_image(v.mlx.mlx, 1920, 1080);
	v.mlx.addr = mlx_get_data_addr(v.mlx.img, &v.mlx.bits_per_pixel, &v.mlx.line_length,
								&v.mlx.endian);
    v.map = read_maps(av[1]);
    initialisation(&v);
    maps_2d(&v);
	mlx_put_image_to_window(v.mlx.mlx, v.mlx.mlx_win, v.mlx.img, 0, 0);
    mlx_hook(v.mlx.mlx_win, 2, 0, key, &v);
    mlx_hook(v.mlx.mlx_win, 17, 0, destroy, &v);
	mlx_loop(v.mlx.mlx);
}
