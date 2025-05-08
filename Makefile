NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCDIR = src
OBJDIR = obj
INCDIR = includes
LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

SRCS = $(SRCDIR)/main.c
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
OBJ_DIRS = $(OBJDIR)

ifeq ($(shell uname), Darwin) # macOS
	READLINE_DIR := $(shell brew --prefix readline 2>/dev/null || echo "/usr/local")
	LDFLAGS = -L$(READLINE_DIR)/lib -lreadline
	CPPFLAGS = -I$(READLINE_DIR)/include -D_GNU_SOURCE
else # Linux
	LDFLAGS = -lreadline
	CPPFLAGS = -D_GNU_SOURCE
endif

SUCCESS = "\033[1;92m✅ Compilation réussie ! ✅\033[0m"
FAILURE = "\033[1;91m❌ Erreur de compilation ! ❌\033[0m"
LIBFT_COMP = "\033[1;94m🔨 Compilation de la libft... 🔨\033[0m"
MINISHELL_COMP = "\033[1;94m🔨 Compilation de minishell... 🔨\033[0m"
CLEAN_MSG = "\033[1;93m🧹 Nettoyage des fichiers objets... 🧹\033[0m"
FCLEAN_MSG = "\033[1;93m🧹 Nettoyage complet... 🧹\033[0m"

# Compilation complète
all: $(OBJ_DIRS) $(LIBFT) $(NAME)

# Création dossier obj
$(OBJ_DIRS):
	@mkdir -p $@

# Compilation libft
$(LIBFT):
	@echo $(LIBFT_COMP)
	@$(MAKE) -C $(LIBFTDIR)

# Compilation de minishell
$(NAME): $(OBJS) $(LIBFT)
	@echo $(MINISHELL_COMP)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFTDIR) -lft -o $(NAME) $(LDFLAGS) && echo $(SUCCESS) || echo $(FAILURE)

# Compilation des .o
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJ_DIRS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -I$(INCDIR) -I$(LIBFTDIR) -c $< -o $@

# Nettoyage des objets
clean:
	@echo $(CLEAN_MSG)
	@$(RM) $(OBJS)
	@rm -rf $(OBJDIR) 2>/dev/null || true
	@$(MAKE) -C $(LIBFTDIR) clean

# Nettoyage complet
fclean: clean
	@echo $(FCLEAN_MSG)
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFTDIR) fclean

# Rebuild complet
re: fclean all
