/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:08:06 by mg                #+#    #+#             */
/*   Updated: 2025/05/27 21:27:19 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Crée un nouveau token.
 */
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

	start = lexer->position;
	while (lexer->current_char && !is_whitespace(lexer->current_char)
		&& !is_special_char(lexer->current_char))
		advance_lexer(lexer);
	value = ft_substr(lexer->input, start, lexer->position - start);
	if (!value)
		return (NULL);
	return (create_token(WORD, value, start));
}


/**
 * Tokenise un opérateur.
*/
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
