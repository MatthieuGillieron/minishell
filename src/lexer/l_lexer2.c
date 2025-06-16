#include "../includes/minishell.h"

static int	process_tokens(t_lexer *lexer, t_token **tokens)
{
	t_token	*token;
	int		i;

	i = 0;
	while (1)
	{
		token = get_next_token(lexer);
		if (!token)
			break ;
		tokens[i++] = token;
		if (token->type == END_OF_INPUT || i >= 1024)
			break ;
	}
	tokens[i] = NULL;
	return (i);
}

/**
 * tokenize_input - Tokenise une chaîne d'entrée
 * @input: La chaîne à tokeniser
 * @return Un tableau de tokens, ou NULL en cas d'erreur
 */
t_token	**tokenize_input(char *input)
{
	t_lexer	*lexer;
	t_token	**tokens;

	lexer = init_lexer(input);
	if (!lexer)
		return (NULL);
	tokens = malloc(sizeof(t_token *) * 1024);
	if (!tokens)
	{
		free(lexer);
		return (NULL);
	}
	process_tokens(lexer, tokens);
	free(lexer);
	return (tokens);
}
