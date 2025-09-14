# ─── Variables ────────────────────────────────────────────────────────────────
CC        := cc
CFLAGS    := -g -I includes -Wall -Werror -Wextra

MLXDIR    := ./minilibx-linux
MLX       := $(MLXDIR)/libmlx.a
LIBS      := -L$(MLXDIR) -lmlx -lXext -lX11 -lm

LDFLAGS   := -Llibft/printf -lftprintf \
              -Llibft       -lft      \
              $(LIBS)

NAME      := cub3D
SRC_DIR   := srcs
OBJ_DIR   := includes/build

SRCS := \
    parsing.c          	\
    cub3d_handling.c   	\
    main.c             	\
    utils.c            	\
    check_data.c       	\
    check_map.c        	\
    setup_map.c        	\
    flood_fill.c       	\
    setting_data.c     	\
    color_handler.c		\
 	ovl_pixels.c 		\
	ovl_key.c 			\
	key_diff.c			\
	key_diff2.c			\
	key_diff3.c			\
	movement.c			\
 	ovl_sky.c   		\
 	ovl_raycast.c		\
 	ovl_raycast2.c		\
	utils_texture.c \
	helper.c\
	helpp.c \
	spwan.c \
	help2.c\
	texture.c			\
	render_frame.c		\
	init.c

SRCS := $(addprefix $(SRC_DIR)/,$(SRCS))
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

HEADERS  := includes/cub3d.h

# ─── Rules ─────────────────────────────────────────────────────────────────────

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	@$(MAKE) -C libft/printf
	@$(MAKE) -C libft
	@$(MAKE) -C $(MLXDIR)              # build MiniLibX
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) -C libft/printf clean
	@$(MAKE) -C libft clean
	@$(MAKE) -C $(MLXDIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C libft/printf fclean
	@$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
