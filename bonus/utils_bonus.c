/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 04:24:45 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/20 02:22:22 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3D.h"

t_object *copie_node(t_object *src)
{
	t_object *node;

	node = malloc(sizeof(t_object));
	if(!node)
		ft_error("Alocate copie node failed");
	ft_memmove(node, src, sizeof(t_object) - sizeof(void *));
	node->next = NULL;
	return(node);
}

t_object *copie_list( t_object *copie)
{
	t_object *tmp;
	t_object *node;

	node = NULL;
	tmp = copie;
	while (tmp)
	{
		addobjt(&node, copie_node(tmp));
		tmp = tmp->next;
	}
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

void	checker_bonus(t_data *v)
{
	int	j;
	int	i;
	int k;

	j = -1;
	k = 0;
	v->sprite = NULL;
	if (v->sprt.count_sprites)
	{
		v->sprite = malloc(sizeof(t_GetSprites) * v->sprt.count_sprites);
		if(!v->sprite)
			ft_error("Allocate t_sprites failed");
	}
	while (v->pars.map[++j])
	{
		i = -1;
		while (v->pars.map[j][++i])
		{
			if ((v->pars.map[j][i] == '2' && (v->pars.map[j + 1][i] != '1' || v->pars.map[j - 1][i] != '1')) && (v->pars.map[j][i] == '2' && (v->pars.map[j][i + 1] != '1' || v->pars.map[j][i - 1] != '1')))
				duplicate_error(&v->pars); //set an error
			if (v->pars.map[j][i] == '3')
				_sprites(v, k++, i, j);
		}
	}
}