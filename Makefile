DEFAULT	:=	\e(B\e[m
RED		:=	\e[31m
GREEN	:=	\e[32m
ORANGE	:=	\e[33m
BLUE	:=	\e[34m
PURPLE	:=	\e[35m
CYAN	:=	\e[36m

NAME		:=	cub3D

INC_PATH	:=	inc
SRC_PATH	:=	src
OBJ_PATH	:=	obj

LIBFT_PATH	:=	libft
LIBFT_INC	:=	$(LIBFT_PATH)/includes
LIBFT		:=	$(LIBFT_PATH)/libft.a
LIBFT_NAME	:=	ft

MLX_TGZ		:=	mlx.tgz
MLX_PATH	:=	mlx
MLX_INC		:=	$(MLX_PATH)
MLX			:=	$(MLX_PATH)/libmlx.a
MLX_NAME	:=	mlx

SRC_FILES	:=	\
				main.c				\
				hook.c				\
				formattedMap.c		\
				identifiedParts.c	\
				identifiedMap.c		\
				player.c			\
				window.c			\

OBJ_FILES	:=	$(SRC_FILES:.c=.o)

SRC			:=	$(addprefix $(SRC_PATH)/, $(SRC_FILES))
OBJ			:=	$(addprefix $(OBJ_PATH)/, $(OBJ_FILES))

# ---------------------------------------- #
CC+FLAGS	:=	cc -Wall -Werror -Wextra -g3
MLXFLAGS	:=	-lmlx -lXext -lX11
RM			:=	rm -rf
# ---------------------------------------- #
$(NAME)			:	$(MLX) $(LIBFT) $(OBJ_PATH) $(OBJ)
					@$(CC+FLAGS) $(OBJ) -o $@ -L$(LIBFT_PATH) -l$(LIBFT_NAME) -L$(MLX_PATH) -l$(MLX_NAME) $(MLXFLAGS)
					@echo "$(CYAN)Successfully linked the objects into $(ORANGE)$(NAME)$(DEFAULT)"

$(OBJ_PATH)		:
					@mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o	:	$(SRC_PATH)/%.c
					@$(CC+FLAGS) -c $< -o $@ -I$(LIBFT_INC) -I$(MLX_INC) -I$(INC_PATH)
					@echo "$(GREEN)Compiled $(PURPLE)$<$(DEFAULT)"

$(MLX)			:	$(MLX_PATH)
					@make -s -C $(MLX_PATH)

$(LIBFT)		:	$(LIBFT_PATH)
					@make -s -C $(LIBFT_PATH)

$(MLX_PATH)		:	$(MLX_TGZ)
					@if [ ! -d "$(MLX_PATH)" ]; then \
						tar -x -f $(MLX_TGZ); \
						echo "$(GREEN)Extracted $(PURPLE)$(MLX_TGZ)$(DEFAULT)"; \
					fi
# ---------------------------------------- #
.PHONY			:	clean cleanobj cleanlibs fclean re

all				:	$(NAME)

clean			:	cleanobj cleanlibs

cleanobj		:
					@$(RM) $(OBJ_PATH)
					@echo "$(RED)Removed $(BLUE)$(NAME)$(RED) objects$(DEFAULT)"

cleanlibs		:
					@if [ -d "libft" ]; then \
						make clean -s -C libft; \
					fi
					@if [ -d "mlx" ]; then \
						make clean -s -C mlx; \
					fi
					@echo "$(RED)Removed $(BLUE)$(MLX_PATH)$(RED) objects$(DEFAULT)"

fclean			:	clean
					@$(RM) $(NAME)
					@echo "$(RED)Removed $(BLUE)$(NAME)$(DEFAULT)"
					@if [ -d "mlx" ]; then \
						$(RM) mlx; \
						echo "$(RED)Removed $(BLUE)$(MLX_PATH)$(RED) library$(DEFAULT)"; \
					fi

re				:	fclean all