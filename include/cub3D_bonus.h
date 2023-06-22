/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 05:15:03 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/22 05:54:21 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H
# define SPRITE 33
# define DOOR 23

typedef struct s_GetSprites
{
	int				i;
	int				j;
	double			xs;
	double			ys;
}					t_GetSprites;

typedef struct s_sprites
{
	unsigned int	**sprite_buff;
	int				sprite_width;
	int				sprite_height;
	int				sprite_line;
	int				count_sprites;
	int				frames;
	int				ind_sprite_text;
}					t_sprites;

typedef struct s_door
{
	unsigned int	**door_buff;
	int				door_width;
	int				door_height;
	int				door_line;
}					t_door;

typedef struct s_object
{
	int				type;
	double			x;
	double			y;
	double			rydis;
	double			rydis_fbw;
	int				hitw;
	double			diemension;
	double			x0;
	double			x1;
	double			y0;
	double			y1;
	struct s_object	*next;
}					t_object;

typedef struct s_minimap
{
	double			raduis;
	double			trans_x;
	double			trans_y;
	double			x;
	double			y;
}					t_minimap;

typedef struct s_norme
{
	int				i;
	int				j;
	int				iq;
	double			smal_sidstp;
	double			big_sidstp;
	int				txw;
}					t_norme;

void				cube3D_bonus(t_data *v);
double				raycasting_bonus(t_data *v, t_object **object, double ang);
void				render_wall_bonus(t_data *v, t_object *object, double ang);
int					loop_hook_bonus(void *ptr);
void				dda_door(t_data *v, t_object *object, double y0, double y1);
void				fill_door(t_data *v, int ind);
void				get_text_door(t_data *v);
double				des_betw_2pt(double x0, double y0, double x1, double y1);
int					_sprites(t_data *v, int k, int i, int j);
void				get_text_sprites(t_data *v);
t_object			*visible_sprite(t_data *v);
void				render_sprite_minimap(t_data *v, t_object *sprites);
void				dda_sprite(t_data *v, t_object *object, double y0,
						double y1);
void				fill_sprite(t_data *v, int ind);
void				render_ssprite(t_data *v, t_object *object);
t_object			*newsprite(t_data *v, t_GetSprites s);
t_object			*newdoor(t_data *v, double ryd, int flag);
t_object			*copie_node(t_data *v, t_object *src);
t_object			*copie_list(t_data *v, t_object *copie);
void				addobjt(t_object **lst, t_object *new);
void				clear_objt(t_object **lst);
void				mini_maps(t_data *v, int color);
int					mouse_hook(int x, int y, t_data *v);

#endif