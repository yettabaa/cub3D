/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfoughal <nfoughal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 22:06:30 by nfoughal          #+#    #+#             */
/*   Updated: 2023/06/15 18:38:11 by nfoughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	between_0_255(char *str)
{
	if (ft_atoi(str) >= 0 && ft_atoi(str) <= 255)
		return (1);
	return (0);
}

int	is_number(char c)
{
	int	i;

	i = 0;
	if (c == '\n')
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	if_int(char **split)
{
	int	i;
	int	j;

	i = 0;
	while (split[i])
	{
		j = 0;
		while (split[i][j])
		{
			if (is_number(split[i][j]) == 0)
			{
				free_array(split);
				write(2, "Error most write numbers only\n", 31);
				exit(1);
			}
			j++;
		}
		if (between_0_255(split[i]) == 0)
		{
			free_array(split);
			write(2, "Error numbers must be between 0 and 255\n", 41);
			exit (1);
		}
		i++;
	}
}

void	coma_split(char *str, int value, t_map_result *res)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split(str, ',');
	while (split[i])
	i++;
	if (i != 3)
	{
		free_array(split);
		write(2, "Error: should write 3 numbers\n", 31);
		exit(1);
	}
	if_int(split);
	if (value == 3)
		res->c = create_trgb(0, ft_atoi(split[0]),
				ft_atoi(split[1]), ft_atoi(split[2]));
	if (value == 6)
		res->f = create_trgb(0, ft_atoi(split[0]),
				ft_atoi(split[1]), ft_atoi(split[2]));
	free_array(split);
	free(str);
}

void	check_f_and_c(char *str, t_map_result *res, int value, char **split)
{
	int	coma;
	int	i;

	coma = 0;
	i = 0;
	while (str[i])
	{
		if (str[i++] == ',')
			coma++;
	}
	if (coma != 2)
	{
		free_array(split);
		write(2, "Error formula is incorrect\n", 28);
		exit(1);
	}
	coma_split(str, value, res);
}
