NAME = mlx_map
CC = cc
CFLAGS = -Wall -Wextra -Werror

MLXDIR = .././minilibx-linux
MLX = $(MLXDIR)/libmlx_Linux.a
LIBS = -L$(MLXDIR) -lXext -lX11 -lm

SRC = main.c render.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX) $(LIBS) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all