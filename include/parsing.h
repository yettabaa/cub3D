/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 22:12:45 by nfoughal          #+#    #+#             */
/*   Updated: 2023/06/13 16:12:59 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include<stdio.h>
# include<unistd.h>
# include<stdlib.h>
# include<fcntl.h>
# include "../parsing/get_next_line/get_next_line.h"
# include <mlx.h>
#include <math.h>

typedef struct s_map_result
{
	int		f;
	int		c;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	**map;
	int row;
	int col;
}t_map_result;

int		ft_strcmp(const char *s1, const char *s2);
char	**split_spc_tab(char *str);
void	check_arg(int ac, char **av);
char	**fill_array_map(char **av);
void	if_map_is_valid(int ac, char **av, t_map_result *res);
void	init_map(t_map_result *res);
void	free_array(char **array);
void	split_and_check(char *str, t_map_result *res);
void	if_args_true(char **split, t_map_result *res);
void	check_f_and_c(char *str, t_map_result *res, int value, char **split);
void	coma_split(char *str, int value, t_map_result *res);
void	if_int(char **split);
int		is_number(char c);
int		between_0_255(char *str);
int		create_trgb(int t, int r, int g, int b);
void	wall_check(char **map, char **array);
void	first_and_last(char **map, int row, char **array);
void	first_line(char **map, char **array);
void	last_line(char **map, int last, char **array);
void	check_sides(char **map, char **array);
void	if_different_1(char *str, char **array, char **map);
void	if_allow(char *str, char **array, char **map);
void	if_valid(char **map, char **array);
int		up_and_down(char **map, int *i, int *count, t_map_result	*res);
void	go_down(char **map, int i, t_map_result	*res);
void	fill_down_map(char **map, char **new, char **array);
void	if_empty(char **map);
void	check_0_pos(char *str, char **array, int y, char **map);
int		re_long_line(char **map);
void	fill_spaces(char **p, int row, char **map);
void	map_copy(char **p, char **map);
void	if_valid(char **map, char **array);
int		check_directions(char **map, int y, int x);

#endif
