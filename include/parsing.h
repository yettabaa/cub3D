/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 22:12:45 by nfoughal          #+#    #+#             */
/*   Updated: 2023/06/22 18:14:06 by yettabaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include<stdio.h>
# include<unistd.h>
# include<stdlib.h>
# include<fcntl.h>
# include "../Mandatory/parsing/get_next_line/get_next_line.h"
# include <mlx.h>
# include <math.h>

typedef struct s_data	t_data;
typedef struct s_map_result
{
	int		f;
	int		c;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	**map;
	char	**map2;
	int		y;
	int		x;
	int		i;
	int		j;
	char	palayer_dir;
}t_map_result;

int		ft_strcmp(const char *s1, const char *s2);
char	**split_spc_tab(char *str);
void	check_arg(int ac, char **av);
char	**fill_array_map(char **av);
void	init_map(t_map_result *res);
void	free_array(char **array);
void	split_and_check(char *str, t_map_result *res);
void	if_args_true(char *sub, char* trim, t_map_result *res);
void	check_f_and_c(char *str, t_map_result *res, int value);
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
void	if_valid(char **map, char **array, t_map_result *res);
int		up_and_down(char **map, int *i, int *count, t_map_result	*res);
void	go_down(char **map, int i, t_map_result	*res);
void	fill_down_map(char **map, char **new, char **array);
void	if_empty(char **map);
void	check_0_pos(char *str, char **array, int y, char **map);
int		re_long_line(char **map);
void	fill_spaces(char **p, char **map, t_map_result *res);
void	map_copy(char **p, char **map);
int		check_directions(char **map, int y, int x);
void	parsing(t_data *v, int ac, char **av);
void	parsing_bonus(t_data *v, int ac, char **av);
void	if_duplicate(t_map_result *v);
void	if_duplicate_bonus(t_data *v);
int		tab_spaces_checker(char *str);
void	duplicate_error(t_map_result *res);
int		door_sides(char **map, int y, int x);
void	check_door_pos(char *str, char **array, int y, char **map);
void	checker_bonus(t_data *v);
int		player_position(t_map_result *res);
void	ft_error(const char *error_msg, const char *str);
void	check_null(t_map_result *res);

#endif
