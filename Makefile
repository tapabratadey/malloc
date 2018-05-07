# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tadey <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/04 16:52:14 by tadey             #+#    #+#              #
#    Updated: 2018/05/05 13:27:43 by tadey            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = malloc
FLAGS = -Wall -Wextra -Werror
LIBFT = -L libft/ -lft
CC = gcc
SRC = *.c

all: $(NAME)

$(NAME):
	$(CC) -g $(FLAGS) $(LIBFT) $(SRC) -o $(NAME)

fclean:
	rm -f $(NAME)

re: fclean all
