# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 18:39:51 by yettabaa          #+#    #+#              #
#    Updated: 2023/06/21 04:38:03 by yettabaa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -Iinclude -Ofast -g -fsanitize=address

MLXFLAGS =  -lmlx -framework OpenGL -framework AppKit -Iinclude -g -fsanitize=address 

HEADER = ./include/cub3D.h ./include/parsing.h ./Libft/libft.h

MAND =	Mandatory/cub3D.c  Mandatory/raycasting.c Mandatory/rendering_wall.c
		
BONUS = bonus/cub3D_bonus.c bonus/maps_2D.c bonus/raycasting_bonus.c bonus/door.c bonus/utils_bonus.c \
		bonus/sprites.c bonus/render_wall_bonus.c bonus/sprites_init.c \
		Mandatory/raycasting.c Mandatory/rendering_wall.c
		
COMMON = Common/hooks.c Common/cub3D_utils.c Common/shapes.c

pars = 	Mandatory/parsing/parsing.c Mandatory/parsing/split.c Mandatory/parsing/utils.c Mandatory/parsing/get_next_line/get_next_line.c \
		Mandatory/parsing/get_next_line/get_next_line_utils.c Mandatory/parsing/valid_map.c Mandatory/parsing/first_lines.c \
		Mandatory/parsing/walls_first_last.c Mandatory/parsing/walls_sides.c Mandatory/parsing/space_valid.c Mandatory/parsing/up_down.c \
		Mandatory/parsing/player_position.c

parsB = bonus/parsing_bonus/parsing.c bonus/parsing_bonus/split.c bonus/parsing_bonus/utils.c bonus/parsing_bonus/get_next_line/get_next_line.c \
		bonus/parsing_bonus/get_next_line/get_next_line_utils.c bonus/parsing_bonus/valid_map.c bonus/parsing_bonus/first_lines.c \
		bonus/parsing_bonus/walls_first_last.c bonus/parsing_bonus/walls_sides.c bonus/parsing_bonus/space_valid.c bonus/parsing_bonus/up_down.c \
		bonus/parsing_bonus/player_position.c bonus/parsing_bonus/utils1.c
		
OMAND = $(MAND:.c=.o) $(pars:.c=.o) $(COMMON:.c=.o)

OBONUS = $(BONUS:.c=.o) $(parsB:.c=.o) $(COMMON:.c=.o) 


OCOMM = 

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

re:fclean all bonus
