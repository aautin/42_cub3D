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
LIBFT_INC	:=	$(LIBFT_PATH)/inc
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
				formattedParts.c	\
				formattedMap.c		\
				identifiedLine.c	\
				identifiedMap.c		\
				player.c			\
				window.c			\

OBJ_FILES	:=	$(SRC_FILES:.c=.o)

SRC			:=	$(addprefix $(SRC_PATH)/, $(SRC_FILES))
OBJ			:=	$(addprefix $(OBJ_PATH)/, $(OBJ_FILES))
DEP			:=	$(OBJ:.o=.d)

# ---------------------------------------- #
CC			:=	cc
CFLAGS		:=	-Wall -Werror -Wextra -g3 -MMD -MP
RM			:=	rm -rf
LDFLAGS		:=	-L$(LIBFT_PATH) -L$(MLX_PATH) 
LDLIBS		:=	-l$(LIBFT_NAME)  -l$(MLX_NAME) -lXext -lX11
# ---------------------------------------- #
$(NAME)			:	$(MLX) $(LIBFT) $(OBJ_PATH) $(OBJ)
					@$(CC) $(OBJ) -o $@ $(LDFLAGS) $(LDLIBS)
					@echo "$(CYAN)Successfully linked the objects into $(ORANGE)$(NAME)$(DEFAULT)"

$(OBJ_PATH)		:
					@mkdir -p $(OBJ_PATH)

-include $(DEP)

$(OBJ_PATH)/%.o	:	$(SRC_PATH)/%.c
					@$(CC) $(CFLAGS) -c $< -o $@ -I$(LIBFT_INC) -I$(MLX_INC) -I$(INC_PATH)
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

clean			:	cleanobj

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
					@if [ -f "$(LIBFT)" ]; then \
						$(RM) $(LIBFT); \
						echo "$(RED)Removed $(BLUE)$(LIBFT)$(DEFAULT)"; \
					fi
					@if [ -d "mlx" ]; then \
						$(RM) mlx; \
						echo "$(RED)Removed $(BLUE)$(MLX_PATH) library$(DEFAULT)"; \
					fi

re				:	fclean all