
NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCDIR = src
OBJDIR = obj
INCDIR = includes
LIBFTDIR = libft

SRCS = $(SRCDIR)/main.c

OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
OBJ_DIRS = $(OBJDIR)

# Flags for readline library - adaptés pour fonctionner sur différents systèmes
ifeq ($(shell uname), Darwin) # macOS
    READLINE_DIR := $(shell brew --prefix readline 2>/dev/null || echo "/usr/local")
    LDFLAGS = -L$(READLINE_DIR)/lib -lreadline
    CPPFLAGS = -I$(READLINE_DIR)/include -D_GNU_SOURCE
else # Linux et autres
    LDFLAGS = -lreadline
    CPPFLAGS = -D_GNU_SOURCE
endif

# Colors for output messages
SUCCESS = "\033[1;92m✅ Compilation réussie ! ✅\033[0m"
FAILURE = "\033[1;91m❌ Erreur de compilation ! ❌\033[0m"
LIBFT_COMP = "\033[1;94m🔨 Compilation de la libft... 🔨\033[0m"
MINISHELL_COMP = "\033[1;94m🔨 Compilation de minishell... 🔨\033[0m"
CLEAN_MSG = "\033[1;93m🧹 Nettoyage des fichiers objets... 🧹\033[0m"
FCLEAN_MSG = "\033[1;93m🧹 Nettoyage complet... 🧹\033[0m"

all: $(OBJ_DIRS) libft $(NAME)

$(OBJ_DIRS):
	@mkdir -p $@

libft:
	@echo $(LIBFT_COMP)
	@$(MAKE) -C $(LIBFTDIR)

$(NAME): $(OBJS)
	@echo $(MINISHELL_COMP)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFTDIR) -lft $(LDFLAGS) && echo $(SUCCESS) || echo $(FAILURE)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJ_DIRS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -I$(INCDIR) -I$(LIBFTDIR) -c $< -o $@

clean:
	@echo $(CLEAN_MSG)
	@$(RM) $(OBJS)
	@rm -rf $(OBJDIR) 2>/dev/null || true
	@$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	@echo $(FCLEAN_MSG)
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all
