# ─── Variables ────────────────────────────────────────────────────────────────
CC        := cc
CFLAGS    := -Wall -Wextra -Werror -g -I includes
LDFLAGS   := -Llibft/printf -lftprintf \
              -Llibft       -lft      \
              -lmlx -lXext -lX11 -lm

NAME      := cub3d

SRC_DIR   := srcs
OBJ_DIR   := includes/build

SRCS := \
    parsing.c          \
    cub3d_handling.c   \
    main.c             \
    utils.c            \
    check_data.c       \
    check_map.c        \
    setup_map.c        \
    flood_fill.c       \
    setting_data.c     \
    color_handler.c

SRCS := $(addprefix $(SRC_DIR)/,$(SRCS))
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

HEADERS  := includes/cub3d.h

# ─── Rules ─────────────────────────────────────────────────────────────────────

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	@$(MAKE) -C libft/printf
	@$(MAKE) -C libft
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) -C libft/printf clean
	@$(MAKE) -C libft clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C libft/printf fclean
	@$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
