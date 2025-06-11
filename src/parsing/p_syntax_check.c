#include "../../includes/minishell.h"
#include "../../includes/parser.h"

static void print_syntax_error(char *token)
{
	ft_putstr_fd("MNM: syntax error near unexpected token `", 2);
	if (!token || !*token)
		ft_putstr_fd("newline", 2);
	else
		ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
}

static int is_redirection_token(t_token_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT || 
			type == REDIR_APPEND || type == HEREDOC);
}

static int check_consecutive_redirections(t_token **tokens)
{
	int i = 0;
	
	while (tokens[i] && tokens[i]->type != END_OF_INPUT)
	{
		// Vérifier si le token actuel est une redirection
		if (is_redirection_token(tokens[i]->type))
		{
			// Vérifier si le token suivant existe
			if (!tokens[i + 1] || tokens[i + 1]->type == END_OF_INPUT)
			{
				print_syntax_error(NULL);
				return (0);
			}
			
			// Vérifier si le token suivant est une autre redirection
			if (is_redirection_token(tokens[i + 1]->type))
			{
				print_syntax_error(tokens[i + 1]->value);
				return (0);
			}
			
			// Vérifier si le token suivant n'est pas un mot (fichier ou délimiteur)
			if (tokens[i + 1]->type != WORD && tokens[i + 1]->type != SQUOTE && 
				tokens[i + 1]->type != DQUOTE)
			{
				print_syntax_error(tokens[i + 1]->value);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

static int check_pipe_syntax(t_token **tokens)
{
	int i = 0;
	
	// Vérifier si le premier token est un pipe
	if (tokens[0] && tokens[0]->type == PIPE)
	{
		print_syntax_error(tokens[0]->value);
		return (0);
	}
	
	while (tokens[i] && tokens[i]->type != END_OF_INPUT)
	{
		// Vérifier si un pipe est suivi d'un autre pipe ou de la fin
		if (tokens[i]->type == PIPE)
		{
			if (!tokens[i + 1] || tokens[i + 1]->type == END_OF_INPUT || 
				tokens[i + 1]->type == PIPE)
			{
				print_syntax_error(tokens[i + 1] ? tokens[i + 1]->value : NULL);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int check_syntax(t_token **tokens)
{
	if (!tokens || !tokens[0])
		return (1);
	
	// Vérifier la syntaxe des pipes
	if (!check_pipe_syntax(tokens))
		return (0);
	
	// Vérifier les redirections
	if (!check_consecutive_redirections(tokens))
		return (0);
	
	return (1);
}
