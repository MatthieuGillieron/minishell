/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:20:06 by mg                #+#    #+#             */
/*   Updated: 2025/05/18 15:51:44 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H


//forward dec.

struct s_token;
typedef struct s_token t_token;
typedef enum e_token_type	t_token_type;


typedef enum e_redir_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND_OUT,
	REDIR_HEREDOC_OUT
}	t_redir_type;


typedef struct s_redirect
{
	t_redir_type		type;
	char				*file_or_delimiter;
	struct s_redirect	*next;

}	t_redirect;

typedef struct s_simple_cmd
{
	char		**args;
	int			arg_count;
	t_redirect	*redirects;
}	t_simple_cmd;


// Structure pour un pipeline de commandes
typedef struct s_command
{
	t_simple_cmd	**commands;
	int				cmd_count;
}	t_command;

// Fonction principale du parser
t_command *parse_tokens(t_token **tokens);

// Sous-fonctions du parser
t_simple_cmd *parse_simple_command(t_token ***tokens_ptr);
t_redirect *parse_redirection(t_token ***tokens_ptr, t_token_type redir_type);
void free_command(t_command *cmd);

// Ajoutez cette ligne pour déclarer print_command
void print_command(t_command *cmd);

// Fonction de conversion
t_redir_type token_to_redir_type(t_token_type token_type);

#endif