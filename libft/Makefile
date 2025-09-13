CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
ARFLAGS = rcs
SRCS = ft_toupper.c ft_tolower.c ft_isalpha.c ft_memset.c ft_bzero.c ft_atoi.c ft_isdigit.c \
	ft_strtrim.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_split.c ft_putstr_fd.c ft_strcmp.c ft_2dlen.c\
	ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c get_next_line.c get_next_line_utils.c linked_list.c\
	ft_strchr.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_atoi_hexa.c ft_strncpy.c ft_mod.c \
	ft_strncmp.c ft_strlen.c ft_strrchr.c ft_memcpy.c ft_memmove.c ft_strnstr.c ft_power.c ft_strfchr.c ft_mult_split.c\
	ft_strlcpy.c ft_strlcat.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_abs.c ft_hexa_to_int.c ft_setup_mult_split.c\
	
SRCSB =	ft_lstlast.c ft_lstsize.c ft_lstadd_front.c ft_lstadd_back.c ft_lstnew.c


OBJS_DIR = build
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
OBJSB = $(SRCSB:%.c=$(OBJS_DIR)/%.o)
all: $(NAME)
HIDE = $(if $(set),, @)

$(NAME): $(OBJS)
	$(HIDE) ar $(ARFLAGS) $@ $^

bonus: $(NAME) $(OBJSB)
	$(HIDE) ar $(ARFLAGS) $(NAME) $(OBJSB)

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(OBJS_DIR)
	$(HIDE) $(CC) $(CFLAGS) -c $< -o $@

clean:
	$(HIDE) rm -f $(OBJS) $(OBJSB)
	$(HIDE)rm -df $(OBJS_DIR)

fclean: clean
	$(HIDE) rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
