# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: root <root@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/27 12:41:41 by enorie            #+#    #+#              #
#    Updated: 2024/07/01 13:21:14 by root             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC = gnl/get_next_line_utils.c gnl/get_next_line.c free.c utils.c utils2.c \
			utils3.c pos.c raycaster.c move.c mlx.c main.c

CC = cc -Ilibft -Ignl -Imlx_linux -Iincludes -Wall -Wextra -Werror -g3

MLX = mlx_linux/libmlx.a

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(MLX) $(OBJ)
	make -C libft
	$(CC) $(OBJ) -Llibft -l:libft.a -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)

$(MLX):
	@if [ ! -d "mlx_linux" ]; then git clone https://github.com/42paris/minilibx-linux.git mlx_linux; fi
	@if [ ! -f "mlx_linux/libmlx.a" ]; then make -C mlx_linux; fi

.c.o:
		$(CC) -c $< -o $(<:.c=.o)

clean:
	make -C libft clean
	rm -f $(OBJ)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)
	rm -rf mlx_linux

re: fclean all

.PHONY: all clean fclean re
