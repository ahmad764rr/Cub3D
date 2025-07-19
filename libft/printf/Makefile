CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a
ARFLAGS = rcs
SRCS = ft_printf.c \
	 ft_print_hex.c \
	 ft_put.c

OBJS_DIR = build
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
HIDE = $(if $(set),, @)
# OBJS =  $(SRCS:.c=.o)
#creating the statico librere
all: $(NAME)
#now we compile the source files (build them and turning them into objects)
#$< means the %.c (requirements) and the $@ means the target which is %.o
%.o:  	%.c
	$(HIDE)$(CC) $(CFLAGS) -c $< -o $@
$(NAME): $(OBJS)
	$(HIDE)ar $(ARFLAGS) $@ $^

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(OBJS_DIR)
	$(HIDE)$(CC) $(CFLAGS) -c $< -o $@

#here we remove the object files (.o) that were created
clean:
	$(HIDE)rm -f $(OBJS)
	$(HIDE)rm -df $(OBJS_DIR)
#we just remove the library files here
fclean: clean
	$(HIDE)rm -f $(NAME)
#here we rebuild everything, by deleting and redoing all of the steps again
re: fclean all

.PHONY: all clean fclean re

