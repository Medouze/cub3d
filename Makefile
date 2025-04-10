# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I $(LIBFT_INC) -g -fsanitize=address -O3
MLX_FLAGS = -lX11 -lXext -lXrandr -lXrender -lXfixes -lm -lbsd

# Directories
SRC_DIR = srcs
OBJ_DIR = obj
OBJ_FOLDER = obj
LIBFT_DIR = libft

# Name
NAME = cub3D
LIBFT = $(LIBFT_DIR)/libft.a
MLX_LIB = minilibx-linux/libmlx.a

# Header
INC = includes
LIBFT_INC = libft/includes
MLX_INC = minilibx-linux

# Source and Object files
SRC_LIST = main.c\
			render/key_hook.c\
			render/init.c\
			render/rendering.c\
			render/destroy_window.c\
			render/minimap.c\
			render/utils.c\
			parser/get_infos.c\
			parser/init.c\
			parser/rgb.c\
			parser/check_file.c\
			parser/map.c\
			parser/map_utils.c\
			parser/parser.c\
			utils/utils.c\
			utils/utils2.c\
			utils/utils3.c\
			error/error.c\


SRC = $(addprefix $(SRC_DIR)/,$(SRC_LIST))
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC_LIST:.c=.o))

# Colors
YELLOW = \033[0;33m
RED = \033[0;31m
RESET = \033[0m

# Main
all: $(OBJ_DIR) $(NAME)

# Create path for object
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/render
	@mkdir -p $(OBJ_DIR)/error
	@mkdir -p $(OBJ_DIR)/parser
	@mkdir -p $(OBJ_DIR)/utils

# Linking object files
$(NAME): $(MLX_LIB) $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) -I $(INC) $(OBJ) $(LIBFT) $(MLX_LIB) -o $(NAME) $(MLX_FLAGS)
	@echo "$(YELLOW)Exec $(NAME) created.$(RESET)"

# Compiling source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC) $(LIBFT_INC) $(MLX_INC)
	@$(CC) $(CFLAGS) -I $(INC) -I $(MLX_INC) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR) --no-print-directory

$(MLX_LIB):
	@make -C $(MLX_INC) --no-print-directory

clean:
	@rm -rf $(OBJ_FOLDER)
	@make clean -C $(LIBFT_DIR) --no-print-directory
	@make clean -C $(MLX_INC) --no-print-directory
	@echo "$(RED)cub3d: Cleaned object files$(RESET)"

fclean:
	@rm -f $(NAME)
	@rm -rf $(OBJ_FOLDER)
	@rm -rf minilibx-linux/obj
	@make fclean -C $(LIBFT_DIR) --no-print-directory
	@echo "$(RED)cub3d: Removed binary files$(RESET)"

re: fclean all

norm:
	@norminette includes
	@norminette libft
	@norminette src

test: all
	./$(NAME) maps/maptest.cub

leak: all
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) maps/maptest.cub

.PHONY: all clean fclean re norm