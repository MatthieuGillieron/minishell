/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_token2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:10:51 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:10:51 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * read_word_segment - Lit un segment de mot jusqu'à un caractère spécial
 * @lexer: Le lexer contenant l'entrée
 * @return Le segment lu, ou NULL en cas d'erreur
 */
static char	*read_word_segment(t_lexer *lexer)
{
	size_t	start;
	char	*segment;

	start = lexer->position;
	while (lexer->current_char && !is_whitespace(lexer->current_char)
		&& !is_special_char(lexer->current_char)
		&& !is_quote(lexer->current_char))
		advance_lexer(lexer);
	segment = ft_substr(lexer->input, start, lexer->position - start);
	return (segment);
}

/**
 * process_quote_in_word - Traite une citation dans un mot
 * @lexer: Le lexer contenant l'entrée
 * @value: La valeur actuelle du mot
 * @return La nouvelle valeur du mot avec la citation, ou NULL en cas d'erreur
 */
static char	*process_quote_in_word(t_lexer *lexer, char *value)
{
	t_token	*quote_token;
	char	*quote_content;
	char	*result;

	if (lexer->current_char == '"')
		quote_token = tokenize_dquote(lexer);
	else
		quote_token = tokenize_squote(lexer);
	if (!quote_token)
		return (NULL);
	quote_content = quote_token->value;
	result = ft_strjoin(value, quote_content);
	free_token(quote_token);
	return (result);
}

static char	*process_word_segments(t_lexer *lexer, char *value)
{
	char	*temp;
	char	*new_value;

	temp = read_word_segment(lexer);
	if (!temp)
		return (value);
	new_value = ft_strjoin(value, temp);
	free(temp);
	if (!new_value)
		return (NULL);
	return (new_value);
}

t_token	*tokenize_word(t_lexer *lexer)
{
	size_t	start;
	char	*value;
	char	*temp;
	t_token	*token;

	start = lexer->position;
	value = read_word_segment(lexer);
	if (!value)
		return (NULL);
	while (lexer->current_char && is_quote(lexer->current_char))
	{
		temp = process_quote_in_word(lexer, value);
		free(value);
		if (!temp)
			return (NULL);
		value = temp;
		temp = process_word_segments(lexer, value);
		free(value);
		if (!temp)
			return (NULL);
		value = temp;
	}
	token = create_token(WORD, value, start);
	free(value);
	return (token);
}
