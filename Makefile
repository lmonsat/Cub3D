# Variables
NAME = cube3d
CC = cc
CFLAGS = -I./include/mlx_linux -g #-Wall -Wextra -Werror
SRC_DIR = src
OBJ_DIR = obj
INCLUDE = include
LIBFT_DIR = include/Libft_plus
LIBFT = $(LIBFT_DIR)/libft.a
LDFLAGS = -L./include/mlx_linux -lmlx_Linux
LDLIBS = -I./include/mlx_linux -lXext -lX11 -lm -lz

# SRC and OBJ files
SRC = main.c parsing.c utils.c raycasting.c gameplay.c get_next_line.c get_next_line_utils.c mlx_functions.c mapping.c  requested_player_move.c player_move.c draw_lines.c
SRCS = $(addprefix $(SRC_DIR)/, $(SRC))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# Colors
B_BLUE = \033[1;36m
B_GREEN = \033[1;32m
B_WHITE = \033[1;37m
RESET = \033[0m

# Rules
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo "\n$(B_BLUE)Compiling $(NAME)...$(B_WHITE)\n"
	$(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) -I $(INCLUDE) -o $(NAME) $(LIBFT)
	@echo "\n$(B_GREEN)$(NAME) compiled successfully!$(B_WHITE)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	@echo "\n$(B_BLUE)Cleaning $(NAME) objs and objs directory...$(B_WHITE)\n"
	rm -rf $(OBJ_DIR)
	@echo "\n$(B_BLUE)Cleaning libft directory...$(B_WHITE)\n"
	$(MAKE) -C $(LIBFT_DIR) clean
	@echo "\n$(B_GREEN)Objs files was removed successfully!$(B_WHITE)\n"
	@echo "$(RESET)"

fclean: clean
	@echo "\n$(B_BLUE)Removing executables...$(B_WHITE)\n"
	rm -rf $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "\n$(B_GREEN)All files was removed successfully!$(B_WHITE)\n"
	@echo "$(RESET)"

re: fclean all

.PHONY: all clean fclean re
