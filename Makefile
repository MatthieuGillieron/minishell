NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCDIR = src
OBJDIR = obj
INCDIR = includes
LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

SRCS := $(shell find $(SRCDIR) -type f -name "*.c" | sort)

# Modification importante ici pour conserver la structure de dossiers
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Création dynamique de la liste des dossiers objets nécessaires
# Cette commande extrait tous les dossiers présents dans les chemins d'objets
OBJ_DIRS := $(shell dirname $(OBJS) | sort | uniq)

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
SUCCESS = "\033[1;92m Compilation réussie ! ✅\033[0m"
FAILURE = "\033[1;91m❌ Erreur de compilation ! ❌\033[0m"
LIBFT_COMP = "\033[1;94m🔨 Compilation de la libft... 🔨\033[0m"
MINISHELL_COMP = "\033[1;94m🔨 Compilation de minishell... 🔨\033[0m"
CLEAN_MSG = "\033[1;93m🧹 Nettoyage des fichiers objets... 🧹\033[0m"
FCLEAN_MSG = "\033[1;93m🧹 Nettoyage complet... 🧹\033[0m"
NO_CHANGES = "\033[1;96m🔄 Aucun changement nécessaire 🔄\033[0m"

# Suppression de la fonction print_success et utilisation d'une méthode plus directe

all: $(OBJ_DIRS) libft_make $(NAME)

# Création des répertoires d'objets
$(OBJ_DIRS):
	@mkdir -p $@

# Règle pour compiler libft avec messages
libft_make: $(LIBFT)

# Règle pour la libft qui évite les relinks
$(LIBFT):
	@echo $(LIBFT_COMP)
	@$(MAKE) -C $(LIBFTDIR) || (echo $(FAILURE) && exit 1)

# Version simplifiée qui évite les problèmes de caractères spéciaux
$(NAME): $(OBJS) $(LIBFT)
	@echo $(MINISHELL_COMP)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(LDFLAGS) && { \
        echo "\033[1;35m"; \
        echo "                                  __              ___    ___      "; \
        echo "           __          __        /\ \            /\_ \  /\_ \     "; \
        echo "  ___ ___ /\_\    ___ /\_\    ___\ \ \___      __\//\ \ \//\ \    "; \
        echo "/' __\` __\`\/\ \ /' _ \`\/\ \  /',__\ \  _ \`\  /'__\`\\\\ \ \  \ \ \   "; \
        echo "/\ \/\ \/\ \ \ \/\ \/\ \ \ \/\__, \`\ \ \ \ \/\  __/ \_\ \_ \_\ \_ "; \
        echo "\ \_\ \_\ \_\ \_\ \_\ \_\ \_\/\____/\ \_\ \_\ \____\/\____\/\____\\"; \
        echo " \/_/\/_/\/_/\/_/\/_/\/_/\/_/\/___/  \/_/\/_/\/____/\/____/\/____/"; \
        echo "\033[0m"; \
        echo $(SUCCESS); \
    } || { echo $(FAILURE) && exit 1; }
	@touch $@

# Règle modifiée pour la compilation des fichiers objets
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -I$(INCDIR) -I$(LIBFTDIR) -c $< -o $@

clean:
	@echo $(CLEAN_MSG)
	@$(RM) $(OBJS)
	@rm -rf $(OBJDIR) 2>/dev/null || true
	@$(MAKE) -C $(LIBFTDIR) clean

fclean:
	@echo $(FCLEAN_MSG)
	@$(RM) $(NAME)
	@$(RM) $(OBJS)
	@rm -rf $(OBJDIR) 2>/dev/null || true
	@$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

# Règle pour vérifier les leaks mémoire (utilise valgrind sous Linux et leaks sous macOS)
leaks: $(NAME)
	@echo "\033[1;94m🔍 Vérification des fuites mémoire... 🔍\033[0m"
ifeq ($(shell uname), Darwin)
	@leaks -atExit -- ./$(NAME) || true
else
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)
endif

.PHONY: all clean fclean re libft_make leaks