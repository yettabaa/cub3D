/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:40:09 by nfoughal          #+#    #+#             */
/*   Updated: 2023/06/21 22:38:15 by nfoughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	duplicate_error(t_map_result *res)
{
	free(res->no);
	free(res->so);
	free(res->we);
	free(res->ea);
	free_array(res->map);
	ft_error("need one player's position", "");
}

int	player_position(t_map_result *res)
{
	int	i;
	int	j;

	i = 0;
	while (res->map[i])
	{
		j = 0;
		while (res->map[i][j])
		{
			if (res->map[i][j] == 'S' || res->map[i][j] == 'N'
			|| res->map[i][j] == 'E' || res->map[i][j] == 'W')
			{
				res->y = i;
				res->x = j;
				res->palayer_dir = res->map[i][j];
				return (1);
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	if_duplicate(t_map_result *res)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (res->map[i])
	{
		j = 0;
		while (res->map[i][j])
		{
			if (res->map[i][j] == 'S' || res->map[i][j] == 'N'
			|| res->map[i][j] == 'E' || res->map[i][j] == 'W')
				count++;
			j++;
		}
		i++;
	}
	if (count > 1 || count == 0)
		duplicate_error(res);
}
