/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 04:24:45 by yettabaa          #+#    #+#             */
/*   Updated: 2023/06/17 02:37:47 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3D.h"

void get_text_door(t_data *v)
{
    int i;
	int endian;
    char *itoa;
    char *path;
    void *tx_img;
    
    i = 0;
    v->door.DOOR_buff = malloc(sizeof(unsigned int*) * 34);
    if (!v->door.DOOR_buff)
        ft_error("Allocate door buffer failed");
    while (i <= 32)
    {
        itoa = ft_itoa(i+1);
        path = ft_strjoin3("./textures/DOOR/", itoa, ".xpm");
        // printf("%s\n",path);
        tx_img =  mlx_xpm_file_to_image(v->mlx.mlx, path, &v->door.DOOR_width, &v->door.DOOR_height);
        free(itoa);
        free(path);
        if(!tx_img)
            ft_error("Door PATH");
        v->door.DOOR_buff[i++] = (unsigned int *)mlx_get_data_addr(tx_img, &endian, &v->door.DOOR_line, &endian);
    }

}

void fill_door(t_data *v, int ind)
{    
    v->txt.buff = v->door.DOOR_buff[ind];
    v->txt.width = v->door.DOOR_width;
    v->txt.height = v->door.DOOR_height;
    v->txt.line = v->door.DOOR_line;   
}

t_list_door *newdoor(t_data *v, double ryd, int flag)
{
    t_list_door *nd;
    (void)v;
    
    nd = malloc(sizeof(t_list_door));
    if (!nd)
        ft_error("Allocate new door failed");
	nd->type = DOOR;
	(flag == WALL) && (nd->type = WALL);
	nd->rydis = ryd;
    nd->rydis_fbw = ryd * cos(rad(v->orientation - v->ryc.ang));
	(flag == HORI || flag == VER) && (nd->hitw = flag);
	nd->x = v->x + ryd * cos(rad(v->ryc.ang));
	nd->y = v->y + ryd * sin(rad(v->ryc.ang));
	nd->next = NULL;
    return(nd);
}

void	addoor(t_list_door **lst, t_list_door *new)
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

void	clear_door(t_list_door **lst)
{
	t_list_door	*c;

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