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
		$(SRCS_DIR)parsing_types.c \
		$(SRCS_DIR)check_objs.c \
		$(SRCS_DIR)check_cylinder.c \
		$(SRCS_DIR)utils.c \
		$(SRCS_DIR)utils2.c \
		$(SRCS_DIR)init_mlx.c \
		$(SRCS_DIR)draw.c \
		$(SRCS_DIR)sphere.c \
		$(SRCS_DIR)vector.c \
		$(SRCS_DIR)maths_utils.c \
		$(SRCS_DIR)colour_maths.c \
		$(SRCS_DIR)tuple_utils.c \
		$(SRCS_DIR)tuple_utils2.c \
		$(SRCS_DIR)tuple_utils3.c \
		$(SRCS_DIR)ray.c \
		$(SRCS_DIR)cylinder.c \
		$(SRCS_DIR)plane.c \
		$(SRCS_DIR)light.c \
		$(SRCS_DIR)shadow.c \
		$(SRCS_DIR)intersections.c \
		$(SRCS_DIR)keyboard.c \
		$(SRCS_DIR)prepare_initial_computations.c \
		$(SRCS_DIR)actions.c \

OBJS = $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)/%.o)

run: all
	./minirt scene/cylinder_basic.rt

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	cc $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	cc $(CFLAGS) $(INCLUDES) -c $< -o $@

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
