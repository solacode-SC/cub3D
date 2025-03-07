
NAME = cub3D

# Directories
SRC_DIR = srcs
OBJ_DIR = objs
INC_DIR = includes
MLX_DIR = minilibx-linux

# Source files
SRC_FILES = core/main.c \
			core/init.c \
			parsing/parser.c \
			player/input.c \
			rendering/render.c \
			utils/cleanup.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# Compiler flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
# For Linux, use this instead:
# MLXFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C $(MLX_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(MLXFLAGS) -o $(NAME)
	@echo "$(NAME) compiled!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(MLX_DIR) -c $< -o $@

clean:
	@$(MAKE) -C $(MLX_DIR) clean
	@rm -rf $(OBJ_DIR)
	@echo "Object files cleaned!"

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME) removed!"

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus