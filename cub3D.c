/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:39:19 by yettabaa          #+#    #+#             */
/*   Updated: 2023/05/21 18:50:20 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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
        // printf("i = %s\n", str);                       
    }
    s = ft_split(str, '\n');
    return(s);
}
int main(int ac ,char **av)
{
    char **s;
    // (void)av;
    (void)ac;
    // printf("%c\n", s[3][4]);
    void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
    s = read_maps(av[1]);
    maps_2d(&img, s);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}