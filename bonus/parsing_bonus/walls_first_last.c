/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_first_last.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 22:08:12 by nfoughal          #+#    #+#             */
/*   Updated: 2023/06/22 18:18:49 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	last_line(char **map, int last, char **array)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strtrim(map[last], " ");
	while (str[i] != '\n' && str[i] != '\0')
	{
		if (str[i] != '1' && str[i] != ' ')
		{
			free(str);
			free_array(map);
			free_array(array);
			ft_error("character different 1", "");
		}
		i++;
	}
	free(str);
}

void	first_line(char **map, char **array)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strtrim(map[0], " ");
	while (str[i] != '\n' && str[i] != '\0')
	{
		if (str[i] != '1' && str[i] != ' ')
		{
			free(str);
			free_array(map);
			free_array(array);
			ft_error("character different 1", "");
		}
		i++;
	}
	free(str);
}

void	first_and_last(char **map, int row, char **array)
{
	first_line(map, array);
	last_line(map, row - 1, array);
}

void check_null(t_map_result *res)
{
	if(res->ea == NULL || res->we == NULL
	|| res->so == NULL ||res->no == NULL
	||res->c == -1 ||res->f == -1)
		ft_error("missing data", "");
}
