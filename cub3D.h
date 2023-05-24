/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:39:16 by yettabaa          #+#    #+#             */
/*   Updated: 2023/05/24 03:07:46 by yettabaa         ###   ########.fr       */
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

typedef struct	s_mlx {
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_mlx;

typedef struct	s_data {
	
	//map
	char **map;
	int scal;
	//player
	double x;
	double y;
	int angle;
	//raycast
	
	double x_first;
    double y_first;
	
	double x_H1stp;
	double y_H1stp;
	double x_Hstp;
	double y_Hstp;
	
	double x_V1stp;
	double y_V1stp;
	double x_Vstp;
	double y_Vstp;
    
	t_mlx mlx;
}	t_data;



void maps_2d(t_data *v);
// void    maps_2d(t_mlx *img, char **map);
void	my_mlx_pixel_put(t_data *v, int x, int y, int color);
void	dda(t_data *v, double x0, double y0, double x1, double y1, int color);
void rectangle(t_data *v, int x, int y, int color);
void disc(t_data *v, int color);
// void	disc(t_data *v, int x, int y, int radius, int color);

#endif