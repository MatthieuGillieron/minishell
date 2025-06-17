/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:16:22 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:16:23 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <termios.h>
# include "../libft/includes/libft.h"
# include "../includes/signals.h"
# include "../includes/loop.h"
# include "../includes/executor.h"
# include "../includes/path.h"
# include "../includes/builtins.h"
# include "../includes/env.h"
# include "../includes/lexer.h"
# include "../includes/parser.h"

//  *** Forward declarations ***
struct						s_token;
typedef struct s_token		t_token;
struct						s_env;
typedef struct s_env		t_env;
struct						s_lexer;
typedef struct s_lexer		t_lexer;
struct						s_redirect;
typedef struct s_redirect	t_redirect;
struct						s_simple_cmd;
typedef struct s_simple_cmd	t_simple_cmd;
struct						s_command;
typedef struct s_command	t_command;
struct						s_status;
typedef struct s_status		t_status;
struct						s_expand;
typedef struct s_expand		t_expand;

extern int					g_sig_received;

// 	*** COLORS *** 
# define RST		"\033[0m"		
# define RED		"\033[1;31m"	
# define GREEN		"\033[1;32m"	
# define YELLOW		"\033[1;33m"	
# define BLUE		"\033[1;34m"	
# define MAGENTA	"\033[1;35m"	
# define CYAN		"\033[1;36m"	
# define WHITE		"\033[1;37m"

//	*** ENUM *** 
typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	ENV_VAR,
	QUOTE,
	SQUOTE,
	DQUOTE,
	WHITESPACE,
	END_OF_INPUT
}	t_token_type;

//	*** STRUCTURE ***
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	int				position;
	struct s_token	*next;
}	t_token;

typedef struct s_lexer
{
	char	*input;
	size_t	position;
	char	current_char;
}	t_lexer;

typedef struct s_status
{
	t_env	*env;
	int		exit_code;
	int		running;
}	t_status;

#endif