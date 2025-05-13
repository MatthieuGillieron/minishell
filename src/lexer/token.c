/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:08:06 by mg                #+#    #+#             */
/*   Updated: 2025/05/13 16:10:03 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Crée un nouveau token.
 */
t_token *create_token(t_token_type type, char *value, int position)
{
    t_token *token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->type = type;
    token->value = value ? ft_strdup(value) : NULL;
    if (value && !token->value)
    {
        free(token);
        return (NULL);
    }
    token->position = position;
    return (token);
}

void free_token(t_token *token)
{
    if (token)
    {
        free(token->value);
        free(token);
    }
}

/**
 * Affiche tous les tokens pour le débogage.
 */
void print_tokens(t_token **tokens)
{
    int i = 0;

    while (tokens[i])
    {
        printf("Token[%d]: Type=%d, Value=%s\n", i, tokens[i]->type, tokens[i]->value);
        i++;
    }
}

/**
 * Tokenise un mot.
 */
t_token *tokenize_word(t_lexer *lexer)
{
    size_t start = lexer->position;

    while (lexer->current_char && !is_whitespace(lexer->current_char) && !is_special_char(lexer->current_char))
        advance_lexer(lexer);
    char *value = ft_substr(lexer->input, start, lexer->position - start);
    if (!value)
        return (NULL);
    return (create_token(WORD, value, start));
}

/**
 * Tokenise un opérateur.
 */
t_token *tokenize_operator(t_lexer *lexer)
{
    char op = lexer->current_char;

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
