/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:39:16 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/14 05:51:45 by yettabaa         ###   ########.fr       */
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

#define WIDTH 1600
#define HIGHT 1000


#define UP 2
#define DOWN 3
#define LEFT 4
#define RIGHT 5

#define A 0
#define S 1
#define D 2
#define W 13
//text
#define NO 15
#define SO 16
#define WE 17
#define EA 18

#define TEXT 19
#define CEIL 20
#define FLOOR 21

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
	
	double angle_dir;
	int angle_speed;
	int walk_dir;
	int walk_speed;
	double angleOr;
	
}	t_hook;

typedef struct s_door{
	int type;
	int hitw;
    double raydis_door;
	double xd;
	double yd;
    struct s_door *next;
} t_door;

typedef struct	s_data {
	
	//player
	double x;
	double y;
	double scal;
	double orientation;
	double epsilon;
	double raydis;
	double raydis_fishbowl;
	// reder_WALL
	double disProj;
	double x0;
	double y0;
	double y1;
	// texture
	int hitWall;
	
	unsigned int *NO_buff; // 270
	int NO_width;
	int NO_height;
	int NO_line;

	unsigned int *SO_buff; // 90
	int SO_width;
	int SO_height;
	int SO_line;
	
	unsigned int *WE_buff; //0
	int WE_width;
	int WE_height;
	int WE_line;
	
	unsigned int *EA_buff; //180
	int EA_width;
	int EA_height;
	int EA_line;
	
	//door
	double raydis_door;
	double x0_door;

	
	unsigned int *DOOR_buff; //180
	int DOOR_width;
	int DOOR_height;
	int DOOR_line;
	t_door *door;
	
	unsigned int *buff;
	int width;
	int height;
	int line;

	t_hook hook;
	t_map_result pars;
    t_rycast ryc;
	t_mlx mlx;
}	t_data;


// void	my_mlx_pixel_put(t_data *v, int x, int y, unsigned int color);
int	my_mlx_pixel_put(t_data *v, int x, int y, unsigned int color);
void	dda(t_data *v, double x0, double y0, unsigned int color);
// void	dda(t_data *v, double x0, double y0, double x1, double y1, int color);
void rectangle(t_data *v, int x, int y, int color);
void disc(t_data *v, int color);

double	rad(double angle);
double normalize_angle_360(double x);
int is(t_data *v, int flag);
void	ft_error(const char *str);

void cube3D(t_data *v);
void rendering_wall(t_data *v);
void update(t_data *v);
//rycast
void steps(t_data *v);
void raycasting(t_data *v);
void visualize_maps(t_data *v, int *i, int *j);
//minimap

// hook
int loop_hook(void *ptr);
int	key_press(int keycode, t_data *v);
int key_release(int keycode, t_data *v);
int destroy(void);
void update(t_data *v);
// textures
void get_textures(t_data *v);
void	dda_textures(t_data *v, double y0, double y1, int flag);
void fill_textures(t_data *v, int flag);
// void	dda_old(t_data *v, double x0, double y0, double x1, double y1, int color);
// bonus
// door
#define SMALL 30
#define BIG 31
#define WALL 22
#define DOOR 23
t_door *newdoor(t_data *v, double ryd, int flag);
void	addoor(t_door **lst, t_door *new);
void cube3D_bonus(t_data *v);
void raycasting_bonus(t_data *v);
void mini_maps(t_data *v, int color);
int loop_hook_bonus(void *ptr);
void render_wall_bonus(t_data *v);
void render_door(t_data *v);
void fill_door(t_data *v);
void get_text_door(t_data *v);
#endif