/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 00:57:13 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/22 05:51:51 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#define SHIFT 65505
#define KEY_A 97
#define KEY_D 100
#define KEY_W 119
#define KEY_S 115
#define ECHAP 65307
#define KEY_LEFT 65361
#define KEY_RIGHT 65363

void	my_exit(t_data *v, const char *str, int status)
{
	if (status)
		ft_putendl_fd((char *)str, STDERR_FILENO);
	free_array(v->pars.map2);
	free(v->pars.so);
	free(v->pars.no);
	free(v->pars.ea);
	free(v->pars.we);
	free(v->sprite);
	free(v->sprt.sprite_buff);
	free(v->door.door_buff);
	clear_collector(v, &v->collect);
	exit(status);
}

int	_destroy(t_data *v)
{
	my_exit(v, "", 0);
	return (0);
}

int	_press(int keycode, t_data *v)
{
	(keycode == KEY_LEFT) && (v->hook.angle_dir = -1);
	(keycode == KEY_RIGHT) && (v->hook.angle_dir = 1);
	(keycode == SHIFT) && (v->hook.walk_speed = 2.5);
	(keycode == KEY_W) && (v->hook.walk_dir = 1);
	if (keycode == ECHAP)
	{
		
		my_exit(v, "", 0);
	}
	else if (keycode == KEY_S)
	{
		v->hook.walk_dir = 1;
		v->hook.angleor = -180;
	}
	else if (keycode == KEY_A)
	{
		v->hook.walk_dir = 1;
		v->hook.angleor = -90;
	}
	else if (keycode == KEY_D)
	{
		v->hook.walk_dir = 1;
		v->hook.angleor = 90;
	}
	return (0);
}

int	_release(int keycode, t_data *v)
{
	(keycode == KEY_LEFT) && (v->hook.angle_dir = 0);
	(keycode == KEY_RIGHT) && (v->hook.angle_dir = 0);
	(keycode == KEY_W) && (v->hook.walk_dir = 0);
	(keycode == SHIFT) && (v->hook.walk_speed = 1.5);
	if (keycode == KEY_S)
	{
		v->hook.walk_dir = 0;
		v->hook.angleor = 0;
	}
	else if (keycode == KEY_A)
	{
		v->hook.walk_dir = 0;
		v->hook.angleor = 0;
	}
	else if (keycode == KEY_D)
	{
		v->hook.walk_dir = 0;
		v->hook.angleor = 0;
	}
	return (0);
}

int	_mouse_hook(int x, int y, t_data *v)
{
	int	width_half;

	width_half = WIDTH / 2;
	if (y > 0 && y < HIGHT && x < WIDTH && x > width_half + 75)
		v->hook.angle_dir = +0.7;
	else if (y > 0 && y < HIGHT && x < WIDTH && x > 0 && x < width_half - 75)
		v->hook.angle_dir = -0.7;
	else
		v->hook.angle_dir = 0;
	return (0);
}

t_collect *creat_node(t_data *v, void *ptr){
	t_collect *node;

	node = malloc(sizeof(t_collect));
	if (!node)
		my_exit(v, "Error\nAlocate copie node failed !", 1);
	node->ptr = ptr;
	node->next = NULL;
	return (node);
}

void	collect_node(t_collect **lst, t_collect *new) {
	if (!lst)
		return;
	if (!*lst) {
		*lst = new;
		return;
	}
	new->next = *lst;
	*lst = new;
}

void	clear_collector(t_data *v, t_collect **lst) {
	t_collect *tmp;

	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		mlx_destroy_image(v->mlx.mlx, tmp->ptr);
		free(tmp);
		tmp = NULL;
	}
	*lst = NULL;
}