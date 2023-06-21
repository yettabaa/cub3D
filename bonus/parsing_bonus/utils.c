/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 22:12:14 by nfoughal          #+#    #+#             */
/*   Updated: 2023/06/21 23:44:10 by nfoughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_map(t_map_result *res)
{
	res->c = 0;
	res->f = 0;
	res->ea = NULL;
	res->map = NULL;
	res->no = NULL;
	res->so = NULL;
	res->we = NULL;
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	check_directions(char **map, int y, int x)
{
	if (map[y][x + 1] == ' ')
		return (0);
	if (map[y][x - 1] == ' ')
		return (0);
	if (map[y + 1][x] == ' ')
		return (0);
	if (map[y - 1][x] == ' ')
		return (0);
	return (1);
}

int	tab_spaces_checker(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] != ' ' && str[i] != '	')
			return (0);
		i++;
	}
	return (1);
}

void	ft_error(const char *error_msg, const char *str)
{
	write(2, "Error\n", 7);
	ft_putendl_fd((char *)error_msg, STDERR_FILENO);
	ft_putendl_fd((char *)str, STDERR_FILENO);
	exit(1);
}
