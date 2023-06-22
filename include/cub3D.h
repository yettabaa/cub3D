/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:39:16 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/22 05:52:20 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../Common/Libft/libft.h"
# include "parsing.h"
# include "cub3D_bonus.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 1600
# define HIGHT 1000
# define UP 2
# define DOWN 3
# define LEFT 4
# define RIGHT 5
# define A 0
# define S 1
# define D 2
# define W 13
# define NO 15
# define SO 16
# define WE 17
# define EA 18
# define TEXT 19
# define CEIL 20
# define FLOOR 21
# define HORI 7
# define VER 8
# define SMALL 30
# define BIG 31
# define WALL 22

typedef struct s_mlx
{
	void			*mlx;
	void			*mlx_win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_mlx;

typedef struct s_rycast
{
	double			x;
	double			y;
	double			ang;
	double			dhside;
	double			dvside;
	double			hdelta;
	double			vdelta;
	double			smal_stp;
	double			big_stp;
}					t_rycast;

typedef struct s_hook
{
	double			angle_dir;
	int				angle_speed;
	double			walk_dir;
	double			walk_speed;
	double			angleor;

}					t_hook;

typedef struct s_textures
{
	int				hitw;
	unsigned int	*nob;
	int				nowdt;
	int				noh;
	int				nol;
	unsigned int	*sob;
	int				sow;
	int				soh;
	int				sol;
	unsigned int	*web;
	int				wew;
	int				weh;
	int				wel;
	unsigned int	*eab;
	int				eaw;
	int				eah;
	int				wal;
	unsigned int	*buff;
	int				width;
	int				height;
	int				line;

}					t_textures;

typedef struct s_data
{
	double			x;
	double			y;
	double			scal;
	double			orientation;
	double			epsil;
	double			raydis;
	double			raydis_fishbowl;
	double			projplane;
	double			xw;
	double			yw;
	int				x_wind;
	double			y0;
	double			y1;
	t_GetSprites	*sprite;
	t_sprites		sprt;
	t_minimap		minimap;
	t_door			door;
	t_textures		tx;
	t_hook			hook;
	t_map_result	pars;
	t_rycast		ryc;
	t_mlx			mlx;
}					t_data;

typedef struct s_norme1
{
	double			var;
	double			x_h1stp;
	double			y_h1stp;
	double			x_hstp;
	double			y_hstp;
	double			x_v1stp;
	double			y_v1stp;
	double			x_vstp;
	double			y_vstp;
}					t_norme1;

typedef struct s_norme2
{
	int				i;
	int				xtx;
	int				ytx;
	double			steps;
}					t_norme2;

int					my_pixel_put(t_data *v, int x, int y, unsigned int color);
void				dda(t_data *v, double x0, double y0, unsigned int color);
void				disc(t_data *v, int color, double radius);
int					check_(t_data *v, int i, int j, int flag);
double				rad(double angle);
double				_deg(double radians);
double				normalize_angle_360(double x);
int					is(t_data *v, double ang, int flag);
void				ft_exit(t_data *v, const char *str, int status);
void				cube3D(t_data *v);
void				rendering_wall(t_data *v, double ang);
void				update(t_data *v);
void				steps(t_data *v, double ang);
double				raycasting(t_data *v, double ang);
void				visualize_maps(t_data *v, double ang, int *i, int *j);
int					loop_hook(void *ptr);
int					key_press(int keycode, t_data *v);
int					key_release(int keycode, t_data *v);
int					destroy(t_data *v);
void				update(t_data *v);
void				get_textures(t_data *v);
void				dda_textures(t_data *v, double y0, double y1, int flag);
void				fill_textures(t_data *v, int flag);

#endif