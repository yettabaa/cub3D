# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 18:39:51 by yettabaa          #+#    #+#              #
#    Updated: 2023/05/26 23:46:28 by yettabaa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -Ofast -fsanitize=address -g 

MLXFLAGS = -lmlx -framework OpenGL -framework AppKit -Ofast -fsanitize=address -g

MAND = cub3D.c maps_2D.c shapes.c

OMAND = $(MAND:.c=.o)

LIBFT = Libft/libft.a

NAME = cub3D

all:	$(NAME)

bonus:

$(NAME):	$(OMAND)
	make -C Libft
	$(CC)  $(MLXFLAGS) $(OMAND) $(LIBFT) -o $(NAME)

%.o:%.c cub3D.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C Libft
	rm -rf $(OMAND)

fclean:clean
	rm -rf $(NAME)

re:fclean all
