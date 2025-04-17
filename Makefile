NAME = minirt

INC_DIR = includes
OBJS_DIR = objs
SRCS_DIR = srcs
MLX_DIR = minilibx-linux

MLX_LIB = $(MLX_DIR)libmlx.a
LIBFT = ./libft/libft.a
INCLUDES = -I. -I$(INC_DIR) -I../libft -I$(MLX_DIR)
CFLAGS = -Wextra -Werror -Wall -g3 #-fsanitize=address
MLX = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

SRCS = $(SRCS_DIR)main.c \
		$(SRCS_DIR)parsing_file.c \
		$(SRCS_DIR)utils.c \
		$(SRCS_DIR)draw.c \
		$(SRCS_DIR)init_mlx.c \

OBJS = $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)/%.o)

all: $(NAME)

run: all
	./minirt scene/scene1.rt

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	@cc $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	@cc $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(LIBFT):
	@make -C ./libft

$(MLX_LIB):
	@make -C $(MLX_DIR)

clean:
	@rm -rf $(OBJS_DIR)
	@make -C ./libft clean
	@make -C $(MLX_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C ./libft fclean

re: fclean all

.PHONY: re fclean all clean
