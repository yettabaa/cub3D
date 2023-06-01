/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:39:16 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/01 02:08:29 by yettabaa         ###   ########.fr       */
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

#define WIDTH 1800
#define HIGHT 720
// #define SMALL 0
// #define BIG 1

#define UP 2
#define DOWN 3
#define LEFT 4
#define RIGHT 5

#define A 0
#define S 1
#define D 2
#define W 13



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
	double scal;
	//player
	double x;
	double y;
	double orientation;
	double epsilon;
	//raycast
	
	double x1;
    double y1;
	double ang;
	
	
	int var;
	int inc ;
	// int stop;
	
	double x_H1stp;
	double y_H1stp;
	double x_Hstp;
	double y_Hstp;
	
	
	double x_V1stp;
	double y_V1stp;
	double x_Vstp;
	double y_Vstp;
	
	double DHside;
	double DVside;
	double Hdelta;
	double Vdelta;
	
	double smal_sidstp;
    double smal_stp;
	double big_sidstp;
    double big_stp;
    
	t_mlx mlx;
}	t_data;


int is(t_data *v, int flag);
void maps_2d(t_data *v);
double normalize_angle_360(double x);
double normalize_angle_180(double x);
void	my_mlx_pixel_put(t_data *v, int x, int y, int color);
void	dda(t_data *v, double x0, double y0, double x1, double y1, int color);
void rectangle(t_data *v, int x, int y, int color);
void disc(t_data *v, int color);
void horisontal_intersections(t_data *v);
double	rad(double angle);
void go_forward(t_data *v);
void go_back(t_data *v);

// void visualize_maps(t_data *v, int *i, int *j);

#endif