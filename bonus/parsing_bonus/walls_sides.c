/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_sides.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 22:08:54 by nfoughal          #+#    #+#             */
/*   Updated: 2023/06/21 23:59:33 by nfoughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	if_allow(char *str, char **array, char **map)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] != '0' && str[i] != '1' && str[i] != 'N' && str[i] != 'S'
			&& str[i] != 'E' && str[i] != 'W' && str[i] != ' ' && str[i] != '2'
			&& str[i] != '3')
		{
			free_array(map);
			free_array(array);
			free(str);
			ft_error("the map must be composed of only 6 possible\
characters:0,1,W,N,S,E", str);
		}
		i++;
	}
}

void	if_different_1(char *str, char **array, char **map)
{
	int	i;

	i = 0;
	if (str[0] != '1' || str[ft_strlen(str) - 1] != '1')
	{
		free_array(map);
		free_array(array);
		free(str);
		ft_error("character different 1", "");
	}
}

void	check_sides(char **map, char **array)
{
	char	*str;
	int		i;

	i = 0;
	while (map[i])
	{
		str = ft_strtrim(map[i], " ");
		if_different_1(str, array, map);
		if_allow(str, array, map);
		free(str);
		i++;
	}
}
