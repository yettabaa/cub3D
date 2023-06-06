#include "cub3D.h"

void	check_arg(int ac, char **av)
{
	if (ac == 2)
	{
		if (ft_strcmp(av[1] + ft_strlen(av[1]) - 4, ".cub") != 0)
		{
			write(2, "Error map name must be written correctly\n", 42);
			write(2, "Example : string.cub\n", 22);
			exit(1);
		}
	}
	else
	{
		write(2, "Error incorrect formula ! \n", 28);
		exit (1);
	}
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
	// if(fd == -1)
	// 	ft_error();
	line = get_next_line(fd);
	// if(line == NULL)
	// 	ft_map_error();
	count = map_line_count(fd, line);
	close(fd);
	fd = open(av[1], O_RDONLY);
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		exit(1);
	fill_map(array, fd);
	close(fd);
	return (array);
}
