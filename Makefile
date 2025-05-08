NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCDIR = src
OBJDIR = obj
INCDIR = includes
LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

# Ajouter tous les fichiers source nécessaires
SRCS = $(SRCDIR)/main.c \
		$(SRCDIR)/signals/signals.c \
		$(SRCDIR)/loops/loop.c

# Modification importante ici pour conserver la structure de dossiers
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
# Création de la liste des dossiers objets nécessaires
OBJ_DIRS = $(OBJDIR) $(OBJDIR)/signals $(OBJDIR)/loops

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

all: $(OBJ_DIRS) $(LIBFT) $(NAME)

# Création des répertoires d'objets
$(OBJ_DIRS):
	@mkdir -p $@

$(LIBFT):
	@echo $(LIBFT_COMP)
	@$(MAKE) -C $(LIBFTDIR)

$(NAME): $(OBJS) $(LIBFT)
	@echo $(MINISHELL_COMP)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(LDFLAGS) && echo $(SUCCESS) || echo $(FAILURE)

# Règle modifiée pour la compilation des fichiers objets
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
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

.PHONY: all clean fclean re