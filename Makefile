# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 18:39:51 by yettabaa          #+#    #+#              #
#    Updated: 2023/06/18 20:09:24 by yettabaa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -Iinclude -fsanitize=address -g -Ofast

MLXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit -Iinclude -fsanitize=address -g 

HEADER = ./include/cub3D.h ./include/parsing.h ./Libft/libft.h

MAND =	Mandatory/cub3D.c Mandatory/shapes.c Mandatory/raycasting.c Mandatory/cub3D_utils.c Mandatory/mouvements.c Mandatory/rendering_wall.c \
		Parsing/split.c Parsing/utils.c Parsing/get_next_line/get_next_line.c \
		Parsing/get_next_line/get_next_line_utils.c Parsing/parsing.c Parsing/first_lines.c \
		Parsing/walls_first_last.c Parsing/walls_sides.c Parsing/space_valid.c Parsing/up_down.c \
		Parsing/player_position.c Parsing/parsing_bonus.c Parsing/fill_map.c bonus/utils_bonus.c

OMAND = $(MAND:.c=.o)

BONUS = bonus/cub3D_bonus.c bonus/maps_2D.c Mandatory/shapes.c Mandatory/raycasting.c bonus/raycasting_bonus.c \
		Mandatory/cub3D_utils.c Mandatory/mouvements.c Mandatory/rendering_wall.c bonus/render_wall_bonus.c\
		Parsing/split.c Parsing/utils.c Parsing/get_next_line/get_next_line.c \
		Parsing/get_next_line/get_next_line_utils.c Parsing/parsing.c Parsing/first_lines.c \
		Parsing/walls_first_last.c Parsing/walls_sides.c Parsing/space_valid.c Parsing/up_down.c \
		bonus/door_render.c bonus/utils_bonus.c Parsing/player_position.c bonus/sprites.c Parsing/parsing_bonus.c \
		Parsing/fill_map.c

OBONUS = $(BONUS:.c=.o)

LIBFT = Libft/libft.a

NAME = cub3D

all:	$(NAME)

%.o: %.c $(HEADER)
	$(CC)  $(CFLAGS) -c $< -o $@ 
	
$(NAME): $(OMAND)
	make -C Libft
	$(CC)  $(MLXFLAGS) $(OMAND) $(LIBFT) -o $(NAME)
	
bonus: $(OBONUS)
	make -C Libft
	$(CC)  $(MLXFLAGS) $(OBONUS) $(LIBFT) -o cub3D_bonus
	
clean: 
	make clean -C Libft
	rm -rf $(OMAND) $(OBONUS)

fclean:clean
	rm -rf $(NAME) $(LIBFT) cub3D_bonus

re:fclean all
