NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCDIR = src
OBJDIR = obj
INCDIR = includes
LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

SRC_FILES = main.c \
			loops/loop.c \
			lexer/l_lexer.c \
			lexer/l_lexer2.c \
			lexer/l_token.c \
			lexer/l_token2.c \
			lexer/l_quotes.c \
			lexer/l_expand.c \
			lexer/l_expand2.c \
			lexer/l_special.c \
			parsing/p_core.c \
			parsing/p_simple.c \
			parsing/p_simple2.c \
			parsing/p_redir.c \
			parsing/p_expand.c \
			parsing/p_syntax_check.c \
			parsing/p_synhax2.c \
			parsing/p_heredoc.c \
			execution/executor.c \
			execution/e_cmd.c \
			execution/e_redir.c \
			execution/e_redir_out.c \
			execution/e_pipe.c \
			execution/e_process.c \
			execution/e_pipeline.c \
			execution/e_heredoc.c \
			builtins/builtins.c \
			builtins/echo.c \
			builtins/echo_status.c \
			builtins/cd.c \
			builtins/pwd.c \
			builtins/env.c \
			builtins/exit.c \
			builtins/export.c \
			builtins/unset.c \
			signals/signals.c \
			signals/signals_handlers.c \
			utils/u_env_principal.c \
			utils/u_env_principal2.c \
			utils/u_env_helpers.c \
			utils/u_env_utilitaires.c \
			utils/u_export.c \
			utils/u_lexer.c \
			utils/u_parse.c \
			utils/u_path.c \
			utils/u_export_alone.c \
			utils/u_path2.c

SRCS = $(addprefix $(SRCDIR)/, $(SRC_FILES))
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

OBJ_DIRS := $(sort $(dir $(OBJS)))

# Flags pour readline - pour fonctionner sur différents OS
ifeq ($(shell uname), Darwin) # macOS
    READLINE_DIR := $(shell brew --prefix readline 2>/dev/null || echo "/usr/local")
    LDFLAGS = -L$(READLINE_DIR)/lib -lreadline
    CPPFLAGS = -I$(READLINE_DIR)/include -D_GNU_SOURCE
else
    LDFLAGS = -lreadline
    CPPFLAGS = -D_GNU_SOURCE
endif

SUCCESS = "\033[1;92m Compilation réussie ! ✅\033[0m"
FAILURE = "\033[1;91m Erreur de compilation ! ❌\033[0m"
LIBFT_COMP = "\033[1;94m Compilation de la libft... 🔨\033[0m"
MINISHELL_COMP = "\033[1;94m Compilation de minishell... 🔨\033[0m"
CLEAN_MSG = "\033[1;93m Nettoyage des fichiers objets... 🧹\033[0m"
FCLEAN_MSG = "\033[1;93m Nettoyage complet... 🧹\033[0m"

all: $(OBJ_DIRS) libft_make $(NAME)

$(OBJ_DIRS):
	@mkdir -p $@

libft_make: $(LIBFT)

$(LIBFT):
	@echo $(LIBFT_COMP)
	@$(MAKE) -C $(LIBFTDIR) || (echo $(FAILURE) && exit 1)

$(NAME): $(OBJS) $(LIBFT)
	@echo $(MINISHELL_COMP)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(LDFLAGS) && { \
		echo $(SUCCESS); \
        echo "\033[1;35m"; \
        echo "                                  __              ___    ___      "; \
        echo "           __          __        /\ \            /\_ \  /\_ \     "; \
        echo "  ___ ___ /\_\    ___ /\_\    ___\ \ \___      __\//\ \ \//\ \    "; \
        echo "/' __\` __\`\/\ \ /' _ \`\/\ \  /',__\ \  _ \`\  /'__\`\\\\ \ \  \ \ \   "; \
        echo "/\ \/\ \/\ \ \ \/\ \/\ \ \ \/\__, \`\ \ \ \ \/\  __/ \_\ \_ \_\ \_ "; \
        echo "\ \_\ \_\ \_\ \_\ \_\ \_\ \_\/\____/\ \_\ \_\ \____\/\____\/\____\\"; \
        echo " \/_/\/_/\/_/\/_/\/_/\/_/\/_/\/___/  \/_/\/_/\/____/\/____/\/____/"; \
        echo "\033[0m"; \
    } || { echo $(FAILURE) && exit 1; }

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -I$(INCDIR) -I$(LIBFTDIR) -c $< -o $@

clean:
	@echo $(CLEAN_MSG)
	@$(RM) -r $(OBJDIR) 2>/dev/null || true
	@$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	@echo $(FCLEAN_MSG)
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

leaks: $(NAME)
	@echo "\033[1;94m Vérification des fuites mémoire... 🔍\033[0m"
ifeq ($(shell uname), Darwin)
	@leaks -atExit -- ./$(NAME) || true
else
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)
endif

.PHONY: all clean fclean re libft_make leaks