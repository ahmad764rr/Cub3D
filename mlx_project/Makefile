NAME = mlx_map
CC = gcc
CFLAGS = 
MLXFLAGS = -lmlx -lXext -lX11 -lm

SRC = main.c render.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(MLXFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
