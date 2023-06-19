/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 04:24:45 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/19 00:09:20 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3D.h"

double des_betw_2pt(double x0, double y0, double x1, double y1)
{
    return(sqrt(pow(fabs(x0 - x1), 2) + pow(fabs(y0 - y1), 2)));
}

void _sprites(t_data *v ,int k, int i, int j)
{
    // printf("%d   %d\n", v->pars.x, v->pars.y);
    // printf("i = %d   j = %d k = %d\n", i ,j, k);
    v->sprite[k].i = i;
    v->sprite[k].j = j;
    v->sprite[k].xs = i * v->scal + v->scal / 2;
    v->sprite[k].ys = j * v->scal + v->scal / 2;
    // printf("x = %f y = %f\n",  v->sprite[k].xs,  v->sprite[k].ys);
    v->sprite[k].rydis = des_betw_2pt(v->sprite[k].xs, v->sprite[k].ys, v->x, v->y);
}

t_object *newsprite(t_data *v, t_sprites sprite)
{
    t_object *node;
    (void)v;
    
    node = malloc(sizeof(t_object));
    if (!node)
        ft_error("Allocate new door failed");
	node->type = SPRITE;
	// node->rydis = ryd;
    // node->rydis_fbw = ryd * cos(Rad(v->orientation - v->ryc.ang));
	// node->renodeered = 0;
	node->i = sprite.i;
	node->j = sprite.j;
	node->x = sprite.xs;
	node->y = sprite.ys;
	node->angle = Deg(atan2(sprite.ys - v->y, sprite.xs - v->x)) - (v->orientation);
	node->rydis = des_betw_2pt(sprite.xs, sprite.ys, v->x, v->y);
	node->rydis_fbw = des_betw_2pt(sprite.xs, sprite.ys, v->x, v->y) * cos(Rad(node->angle));
	// printf("x = %f y = %f ryd = %f\n", sprite.xs, sprite.ys, node->rydis_fbw);
	node->next = NULL;
    return(node);
}



void	addobjt(t_object **lst, t_object *new)
{
	if (!lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	new->next = *lst;
	*lst = new;
}

// t_object	*last(t_object *lst)
// {
// 	while (lst)
// 	{
// 		if (lst->next == NULL)
// 			break ;
// 		lst = lst->next;
// 	}
// 	return (lst);
// }
// void	addback_objt(t_object **lst, t_object *new) // reje3 libft
// {
// 	if (!lst)
// 		return ;
// 	if (*lst == NULL)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	last(*lst)->next = new;
// }


void	clear_objt(t_object **lst)
{
	t_object	*c;

	if (!lst)
		return ;
	c = *lst;
	while (c)
	{
		if (c->next == NULL)
		{
			free((void*)*lst);
			break ;
		}
		c = c->next;
		free((void*)*lst);
		*lst = c;
	}
	*lst = NULL;
}