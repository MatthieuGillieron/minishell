/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_quotes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:10:13 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:10:38 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_escape_char(t_lexer *lexer, char *processed, int *p_index)
{
	if (lexer->current_char == '\\' && lexer->input[lexer->position + 1])
	{
		if (lexer->input[lexer->position + 1] == '"'
			|| lexer->input[lexer->position + 1] == '\\'
			|| lexer->input[lexer->position + 1] == '$')
		{
			advance_lexer(lexer);
			processed[(*p_index)++] = lexer->current_char;
		}
		else
			processed[(*p_index)++] = '\\';
	}
	else
		processed[(*p_index)++] = lexer->current_char;
}

t_token	*tokenize_squote(t_lexer *lexer)
{
	size_t	start;
	char	*value;
	t_token	*token;

	start = lexer->position;
	advance_lexer(lexer);
	while (lexer->current_char && lexer->current_char != '\'')
		advance_lexer(lexer);
	if (lexer->current_char != '\'')
		return (NULL);
	value = ft_substr(lexer->input, start + 1, lexer->position - start - 1);
	advance_lexer(lexer);
	if (!value)
		return (NULL);
	token = create_token(SQUOTE, value, start);
	free(value);
	return (token);
}

static int	process_dquote_content(t_lexer *lexer,
	char *processed, int *p_index)
{
	while (lexer->current_char && lexer->current_char != '"')
	{
		handle_escape_char(lexer, processed, p_index);
		advance_lexer(lexer);
	}
	if (lexer->current_char != '"')
		return (0);
	advance_lexer(lexer);
	processed[*p_index] = '\0';
	return (1);
}

t_token	*tokenize_dquote(t_lexer *lexer)
{
	size_t	start;
	char	*processed;
	int		p_index;
	t_token	*token;

	start = lexer->position;
	advance_lexer(lexer);
	processed = malloc(ft_strlen(lexer->input) + 1);
	if (!processed)
		return (NULL);
	p_index = 0;
	if (!process_dquote_content(lexer, processed, &p_index))
	{
		free(processed);
		return (NULL);
	}
	token = create_token(WORD, processed, start);
	free(processed);
	return (token);
}
