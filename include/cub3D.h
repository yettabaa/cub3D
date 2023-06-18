/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:39:16 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/18 05:07:44 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUB3D_H
# define CUB3D_H
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
	double x;
    double y;
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
	double walk_dir;
	double walk_speed;
	double angleOr;
	
}	t_hook;


typedef struct s_textures{
	
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
	unsigned int *buff;
	int width;
	int height;
	int line;
	
} t_textures;

typedef struct s_door{
	unsigned int **DOOR_buff; //180
	int DOOR_width;
	int DOOR_height;
	int DOOR_line;
} t_door;

typedef struct s_object{   // casting
	int type;
	int hitw; // door wall
	int i; // sprite
	int j; // sprite
	double rendered; //sprite
	double angle;
	double x;
	double y;
	double rydis; // ??
    double rydis_fbw;
    struct s_object *next;
} t_object;

typedef struct s_list_door{ //linked list door
	int type;
	int hitw;
	double rydis;
    double rydis_fbw;
	double x;
	double y;
    struct s_list_door *next;
} t_list_door;


typedef struct s_sprites{
	int i;
	int j;
	double xs;
	double ys;
	double rydis;
	// double visible;
}t_sprites;

typedef struct	s_data {
	
	//player
	double x;
	double y;
	double scal;
	double orientation;
	double epsilon;
	// double *ryd;
	double raydis;
	double raydis_fishbowl;
	// reder_WALL
	double disProj;
	double xw;
	double yw;
	// double disProj;
	int x_wind;
	double y0;
	double y1;
	//sptites
	unsigned int **sprite_buff; //180
	int sprite_width;
	int sprite_height;
	int sprite_line;
	int count_sprites;
	double xs0;
	double xs1;
	double spriteDimension;
	int frames;
	int ind_sprite_text;
	t_sprites *sprite;
	// t_object *sprt;
	//objct
	t_object *object;

	t_door door;
	// t_list_door *list_door;
	t_textures txt;
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
// void disc(t_data *v, int color);
void disc(t_data *v, double x, double y, int color);

double	Rad(double angle);
double Deg(double radians); 
double normalize_angle_360(double x);
int is(t_data *v, double ang, int flag);
void	ft_error(const char *str);
//wall
void cube3D(t_data *v);
void rendering_wall(t_data *v, double ang);
void update(t_data *v);
//rycast
void steps(t_data *v, double ang);
double raycasting(t_data *v, double ang, int hit);
void visualize_maps(t_data *v, double ang, int *i, int *j);
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
void	dda_old(t_data *v, double x0, double y0, double x1, double y1, int color);
// bonus
#define SMALL 30
#define BIG 31
#define WALL 22
#define SPRITE 33
#define DOOR 23
// door
void cube3D_bonus(t_data *v);
double raycasting_bonus(t_data *v, double ang);
void mini_maps(t_data *v, int color);
int loop_hook_bonus(void *ptr);
void render_wall_bonus(t_data *v, double ang);
void render_object(t_data *v);
void fill_door(t_data *v, int ind);
void get_text_door(t_data *v);
// sprites
// void _sprites(t_data *v ,int k, int i, int j);
void get_text_sprites(t_data *v);
void visible_sprite(t_data *v);
// void	dda_sprite(t_data *v, double y0, double y1);
void	dda_sprite(t_data *v, double y0, double y1, double x);
void fill_sprite(t_data *v, int ind);
void render_ssprite(t_data *v);
//utils
double des_betw_2pt(double x0, double y0, double x1, double y1);
//object
t_object *newsprite(t_data *v, t_sprites s);
t_object *newdoor(t_data *v, double ryd, int flag);


void	addobjt(t_object **lst, t_object *new);
void	clear_objt(t_object **lst);

#endif