# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yettabaa <yettabaa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/22 03:34:45 by yettabaa          #+#    #+#              #
#    Updated: 2023/06/22 18:34:20 by yettabaa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

MANDA = ft_strlen.c ft_memset.c ft_memcpy.c ft_memmove.c \
		ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_atoi.c \
		ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

OBJS = $(MANDA:.c=.o)

BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
		ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJSBO = $(BONUS:.c=.o)

NAME = libft.a


all:	$(NAME)

%.o : %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
		ar -rc $(NAME) $(OBJS)
		
bonus:	$(OBJSBO)
		ar -rc $(NAME) $(OBJSBO)
	
clean:
	rm -f $(OBJS) $(OBJSBO)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all bonus clean fclean re