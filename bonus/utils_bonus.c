/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 04:24:45 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/22 05:08:16 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_object	*copie_node(t_data *v, t_object *src)
{
	t_object	*node;

	node = malloc(sizeof(t_object));
	if (!node)
		ft_exit(v, "Error\nAlocate copie node failed !", 1);
	ft_memmove(node, src, sizeof(t_object));
	node->next = NULL;
	return (node);
}

t_object	*copie_list(t_data *v, t_object *copie)
{
	t_object	*tmp;
	t_object	*node;

	node = NULL;
	tmp = copie;
	while (tmp)
	{
		addobjt(&node, copie_node(v, tmp));
		tmp = tmp->next;
	}
	return (node);
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
	t_object	*node;

	while (*lst)
	{
		node = *lst;
		*lst = (*lst)->next;
		free(node);
		node = NULL;
	}
	*lst = NULL;
}

void	checker_bonus(t_data *v)
{
	int	j;
	int	i;
	int	k;

	j = -1;
	k = 0;
	if (v->sprt.count_sprites)
	{
		v->sprite = malloc(sizeof(t_GetSprites) * v->sprt.count_sprites);
		if (!v->sprite)
			ft_exit(v, "Error\nAllocate t_sprites failed !", 1);
	}
	while (v->pars.map2[++j])
	{
		i = -1;
		while (v->pars.map2[j][++i])
		{
			if ((v->pars.map2[j][i] == '2' && (v->pars.map2[j + 1][i] != '1'
				|| v->pars.map2[j - 1][i] != '1'))
				&& (v->pars.map2[j][i] == '2' && (v->pars.map2[j][i + 1] != '1'
						|| v->pars.map2[j][i - 1] != '1')))
				ft_exit(v, "Error\nInvalid placement of a door", 1);
			(v->pars.map2[j][i] == '3') && (_sprites(v, k++, i, j));
		}
	}
}
