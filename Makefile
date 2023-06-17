# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 18:39:51 by yettabaa          #+#    #+#              #
#    Updated: 2023/06/16 23:35:29 by yettabaa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -Iinclude -Ofast -fsanitize=address -g

MLXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit -Iinclude -fsanitize=address -g 

HEADER = ./include/cub3D.h ./include/parsing.h ./Libft/libft.h

MAND =	Mandatory/cub3D.c Mandatory/shapes.c Mandatory/raycasting.c Mandatory/cub3D_utils.c Mandatory/mouvements.c Mandatory/rendering_wall.c \
		parsing/parsing.c parsing/split.c parsing/utils.c parsing/get_next_line/get_next_line.c \
		parsing/get_next_line/get_next_line_utils.c parsing/valid_map.c parsing/first_lines.c \
		parsing/walls_first_last.c parsing/walls_sides.c parsing/space_valid.c parsing/up_down.c \
		parsing/player_position.c 

OMAND = $(MAND:.c=.o)

BONUS = bonus/cub3D_bonus.c bonus/maps_2D.c Mandatory/shapes.c Mandatory/raycasting.c bonus/raycasting_bonus.c \
		Mandatory/cub3D_utils.c Mandatory/mouvements.c Mandatory/rendering_wall.c bonus/render_wall_bonus.c\
		parsing/parsing.c parsing/split.c parsing/utils.c parsing/get_next_line/get_next_line.c \
		parsing/get_next_line/get_next_line_utils.c parsing/valid_map.c parsing/first_lines.c \
		parsing/walls_first_last.c parsing/walls_sides.c parsing/space_valid.c parsing/up_down.c \
		bonus/door_render.c bonus/door_utils.c parsing/player_position.c bonus/sprites.c

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
