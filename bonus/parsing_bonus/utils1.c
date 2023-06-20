/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 19:24:49 by nfoughal          #+#    #+#             */
/*   Updated: 2023/06/17 19:28:48 by nfoughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	door_sides(char **map, int y, int x)
{
	int	up_down;
	int	lift_right;
	printf("x ===> %d  and y ====> %d\n", x, y);
	up_down = 0;
	lift_right = 0;
	if (map[y][x + 1] == '1')
		lift_right++;
	if (map[y][x - 1] == '1')
		lift_right++;
	if (map[y + 1][x] == '1')
		up_down++;
	if (map[y - 1][x] == '1')
		up_down++;
	if(up_down == 2 || lift_right == 2)
		return (1);
	return (0);
}

void	check_door_pos(char *str, char **array, int y, char **map)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '2')
		{
			if (door_sides(map, y, i) == 0)
			{
				free_array(map);
				free_array(array);
				write(2, "Error: the door position is not valid\n", 39);
				exit(1);
			}
		}
		i++;
	}
}