/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 19:12:39 by nfoughal          #+#    #+#             */
/*   Updated: 2023/06/21 23:41:48 by nfoughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_arg(int ac, char **av)
{
	if (ac == 2)
	{
		if (ft_strcmp(av[1] + ft_strlen(av[1]) - 4, ".cub") != 0)
			ft_error("map name must be written correctly ",
				"Example : string.cub");
	}
	else
		ft_error("incorrect formula ! ", "");
}

int	map_line_count(int fd, char *line)
{
	int	i;

	i = 0;
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	return (i);
}

void	fill_map(char **array, int fd)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		array[i] = line;
		line = get_next_line(fd);
		i++;
	}
	array[i] = 0;
}

char	**fill_array_map(char **av)
{
	char	*line;
	char	**array;
	int		fd;
	int		count;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		ft_error("Open : permission denied", "");
	line = get_next_line(fd);
	count = map_line_count(fd, line);
	close(fd);
	fd = open(av[1], O_RDONLY);
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		ft_error("malloc failed", "");
	fill_map(array, fd);
	close(fd);
	return (array);
}
