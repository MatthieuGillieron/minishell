/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:10:07 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:10:07 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lexer	*init_lexer(char *input)
{
	t_lexer	*lexer;

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

void	skip_whitespace(t_lexer *lexer)
{
	while (lexer->current_char && is_whitespace(lexer->current_char))
		advance_lexer(lexer);
}

t_token	*get_next_token(t_lexer *lexer)
{
	skip_whitespace(lexer);
	if (lexer->current_char == '\0')
		return (create_token(END_OF_INPUT, NULL, lexer->position));
	if (lexer->current_char == '\'')
		return (tokenize_squote(lexer));
	if (lexer->current_char == '"')
		return (tokenize_dquote(lexer));
	if (is_special_char(lexer->current_char))
		return (tokenize_operator(lexer));
	if (!is_whitespace(lexer->current_char))
		return (tokenize_word(lexer));
	return (NULL);
}
