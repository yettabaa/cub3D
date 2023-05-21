/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:39:16 by yettabaa          #+#    #+#             */
/*   Updated: 2023/05/21 18:40:30 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUB3D_H
# define CUB3D_H
# ifndef BUFFER_SIZE
# define BUFFER_SIZE 2147483646
# endif
# include "Libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include<limits.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void    rectangle(t_data *img, int x, int y, int hight, int width, int color);
void    maps_2d(t_data *img, char **map);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	dda(t_data *img, double x0, double y0, double x1, double y1, int color);
void	rectangle(t_data *img, int x, int y, int hight, int width, int color);
void	disc(t_data *img, int x, int y, int radius, int color);

#endif