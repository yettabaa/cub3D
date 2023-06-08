# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 18:39:51 by yettabaa          #+#    #+#              #
#    Updated: 2023/06/07 21:04:04 by yettabaa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -Ofast -Iinclude -fsanitize=address -g 

MLXFLAGS = -lmlx -framework OpenGL -framework AppKit -Iinclude -fsanitize=address -g 

HEADER = ./include/cub3D.h ./include/parsing.h ./Libft/libft.h

MAND = cub3D.c maps_2D.c shapes.c raycasting.c cub3D_utils.c mouvements.c rendering_wall.c \
		parsing/parsing.c parsing/split.c parsing/utils.c parsing/get_next_line/get_next_line.c \
		parsing/get_next_line/get_next_line_utils.c parsing/valid_map.c parsing/first_lines.c \
		parsing/walls_first_last.c parsing/walls_sides.c parsing/space_valid.c parsing/up_down.c \

OMAND = $(MAND:.c=.o)

LIBFT = Libft/libft.a

NAME = cub3D

all:	$(NAME)

%.o: %.c $(HEADER)
	$(CC)  $(CFLAGS) -c $< -o $@ 
	
bonus:

$(NAME): $(OMAND)
	make -C Libft
	$(CC)  $(MLXFLAGS) $(OMAND) $(LIBFT) -o $(NAME)

clean: 
	make clean -C Libft
	rm -rf $(OMAND)

fclean:clean
	rm -rf $(NAME) $(LIBFT)

re:fclean all
