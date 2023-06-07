/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:39:16 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/07 05:16:36 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUB3D_H
# define CUB3D_H
# ifndef BUFFER_
# define BUFFER_ 2147483646
# endif
# include "../Libft/libft.h"
# include "parsing.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include<limits.h>

#define WIDTH 2300
#define HIGHT 1300
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

#define HORI 7
#define VER 8

typedef struct	s_mlx {
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_mlx;

typedef struct	s_steps {
	double var;
	double x_H1stp;
	double y_H1stp;
	double x_Hstp;
	double y_Hstp;
	double x_V1stp;
	double y_V1stp;
	double x_Vstp;
	double y_Vstp;
}t_steps;

typedef struct	s_rycast {
	double x1;
    double y1;
	double ang;

	double DHside;
	double DVside;
	double Hdelta;
	double Vdelta;
	
    double smal_stp;
    double big_stp;

} t_rycast;

typedef struct s_hook{
	
	int angle_dir;
	int angle_speed;
	int walk_dir;
	int walk_speed;
	double angleOr;
	
}	t_hook;

typedef struct	s_data {
	
	//player
	double x;
	double y;
	double scal;
	double orientation;
	double epsilon;
	double raydis;
	// 3D
	double disProj;
	double x0;
	double y0;
	double y1;
	// texture
	int hitWall;
	void *no_img;
	unsigned int *no_buff;
	int no_width;
	int no_height;
	int no_bitspp;
	int no_line;
	int no_endian;

	t_hook hook;
	t_map_result pars;
    t_rycast ryc;
	t_mlx mlx;
}	t_data;


void	my_mlx_pixel_put(t_data *v, int x, int y, unsigned int color);
void	dda(t_data *v, double x0, double y0, unsigned int color);
void rectangle(t_data *v, int x, int y, int color);
void disc(t_data *v, int color);

double	rad(double angle);
double normalize_angle_360(double x);
double normalize_angle_180(double x);
int is(t_data *v, int flag);
void steps(t_data *v);
void raycasting(t_data *v);
void cube3D(t_data *v);
void rendering_wall(t_data *v);
void update(t_data *v);

int loop_hook(void *ptr);
int	key_press(int keycode, t_data *v);
int key_release(int keycode, t_data *v);
int destroy(void);
// textures
void fill_textures(t_data *v);
void	dda_textures(t_data *v, double x0, double y0, double x1, double y1);

#endif