/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:53:59 by mg                #+#    #+#             */
/*   Updated: 2025/05/13 16:36:22 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ".././includes/minishell.h"

t_lexer *init_lexer(char *input)
{
	t_lexer *lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->input = input;
	lexer->position = 0;
	lexer->current_char = input[0];
	return (lexer);
}

void	advance_lexer(t_lexer *lexer)
{
	lexer->position++;
	if (lexer->input[lexer->position])
		lexer->current_char = lexer->input[lexer->position];
	else
		lexer->current_char = '\0';
}


void skip_whitespace(t_lexer *lexer)
{
    while (lexer->current_char && is_whitespace(lexer->current_char))
        advance_lexer(lexer);
}

t_token *get_next_token(t_lexer *lexer)
{
    skip_whitespace(lexer);

    if (lexer->current_char == '\0')
        return (create_token(END_OF_INPUT, NULL, lexer->position));
    if (is_special_char(lexer->current_char))
        return (tokenize_operator(lexer));
    if (!is_whitespace(lexer->current_char))
        return (tokenize_word(lexer));
    return (NULL);
}

t_token **tokenize_input(char *input)
{
    t_lexer *lexer = init_lexer(input);
    t_token **tokens = malloc(sizeof(t_token *) * 1024); // Taille arbitraire jsp si c est bien
    int i = 0;

    if (!tokens)
	{
		free(lexer);
        return (NULL);
	}
    while (1)
    {
        t_token *token = get_next_token(lexer);
        if (!token)
            break;
        tokens[i++] = token;
        if (token->type == END_OF_INPUT)
            break;
		if (i >= 1024)
			break;
    }
    tokens[i] = NULL;
    free(lexer);
    return (tokens);
}
