
NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCDIR = src
OBJDIR = obj
INCDIR = includes

SRCS = 

OBJS =
OBJ_DIRS = 

SUCCESS = "\033[1;92m✅ Compilation réussie ! ✅\033[0m"
FAILURE = "\033[1;91m❌ Erreur de compilation ! ❌\033[0m"

all: $(OBJ_DIRS) $(NAME)

$(OBJ_DIRS):
	@mkdir -p $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) && echo $(SUCCESS) || echo $(FAILURE)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJ_DIRS)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@rm -rf $(OBJDIR) 2>/dev/null || true

fclean: clean
	@$(RM) $(NAME)

re: fclean all