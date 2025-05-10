NAME = libft.a

SRC_LIBFT = src/libft/ft_isalpha.c src/libft/ft_isdigit.c src/libft/ft_isalnum.c \
src/libft/ft_isascii.c src/libft/ft_isprint.c src/libft/ft_strlen.c \
src/libft/ft_memset.c src/libft/ft_bzero.c src/libft/ft_memcpy.c \
src/libft/ft_memmove.c src/libft/ft_strlcpy.c src/libft/ft_strlcat.c \
src/libft/ft_toupper.c src/libft/ft_tolower.c src/libft/ft_strchr.c \
src/libft/ft_strrchr.c src/libft/ft_strncmp.c src/libft/ft_memchr.c \
src/libft/ft_memcmp.c src/libft/ft_strnstr.c src/libft/ft_atoi.c \
src/libft/ft_calloc.c src/libft/ft_strdup.c src/libft/ft_substr.c \
src/libft/ft_strjoin.c src/libft/ft_strtrim.c src/libft/ft_split.c \
src/libft/ft_itoa.c src/libft/ft_strmapi.c src/libft/ft_striteri.c \
src/libft/ft_putchar_fd.c src/libft/ft_putstr_fd.c src/libft/ft_putendl_fd.c \
src/libft/ft_putnbr_fd.c src/libft/ft_strcmp.c

SRC_GNL = src/gnl/get_next_line.c src/gnl/get_next_line_utils.c
SRC_PRINTF = src/printf/ft_print.c src/printf/utils.c src/printf/utils_2.c src/printf/utils_3.c

OBJS = $(SRC_LIBFT:.c=.o) $(SRC_GNL:.c=.o) $(SRC_PRINTF:.c=.o)

FLAGS = -Wall -Wextra -Werror -I includes/
CC = gcc
AR = ar rcs
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@ || exit 1

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re