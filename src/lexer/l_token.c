#include "../../includes/minishell.h"

t_token	*create_token(t_token_type type, char *value, int position)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	if (value)
	{
		token->value = ft_strdup(value);
		if (!token->value)
		{
			free(token);
			return (NULL);
		}
	}
	else
		token->value = NULL;
	token->position = position;
	return (token);
}

void	free_token(t_token *token)
{
	if (token)
	{
		free(token->value);
		free(token);
	}
}

t_token	*tokenize_word(t_lexer *lexer)
{
	size_t	start;
	char	*value;
	char	*temp;
	char	*quote_content;
	t_token	*quote_token;

	start = lexer->position;
	while (lexer->current_char && !is_whitespace(lexer->current_char)
		&& !is_special_char(lexer->current_char)
		&& !is_quote(lexer->current_char))
		advance_lexer(lexer);
	value = ft_substr(lexer->input, start, lexer->position - start);
	if (!value)
		return (NULL);
	
	// Si le mot est suivi directement par des guillemets, les fusionner
	while (lexer->current_char && is_quote(lexer->current_char))
	{
		if (lexer->current_char == '"')
			quote_token = tokenize_dquote(lexer);
		else // if (lexer->current_char == '\'')
			quote_token = tokenize_squote(lexer);
		
		if (!quote_token)
		{
			free(value);
			return (NULL);
		}
		
		quote_content = quote_token->value;
		temp = ft_strjoin(value, quote_content);
		free(value);
		free_token(quote_token);
		value = temp;
		
		// Continuer avec le texte après les guillemets s'il y en a
		while (lexer->current_char && !is_whitespace(lexer->current_char)
			&& !is_special_char(lexer->current_char)
			&& !is_quote(lexer->current_char))
		{
			start = lexer->position;
			while (lexer->current_char && !is_whitespace(lexer->current_char)
				&& !is_special_char(lexer->current_char)
				&& !is_quote(lexer->current_char))
				advance_lexer(lexer);
			
			temp = ft_substr(lexer->input, start, lexer->position - start);
			if (!temp)
			{
				free(value);
				return (NULL);
			}
			
			quote_content = ft_strjoin(value, temp);
			free(value);
			free(temp);
			value = quote_content;
		}
	}
	
	return (create_token(WORD, value, start));
}


t_token	*tokenize_operator(t_lexer *lexer)
{
	char	op;

	op = lexer->current_char;
	advance_lexer(lexer);
	if (op == '>' && lexer->current_char == '>')
	{
		advance_lexer(lexer);
		return (create_token(REDIR_APPEND, ">>", lexer->position - 2));
	}
	else if (op == '<' && lexer->current_char == '<')
	{
		advance_lexer(lexer);
		return (create_token(HEREDOC, "<<", lexer->position - 2));
	}
	else if (op == '>')
		return (create_token(REDIR_OUT, ">", lexer->position - 1));
	else if (op == '<')
		return (create_token(REDIR_IN, "<", lexer->position - 1));
	else if (op == '|')
		return (create_token(PIPE, "|", lexer->position - 1));
	return (NULL);
}
