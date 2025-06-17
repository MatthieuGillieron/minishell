/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_lexer2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:10:10 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:10:10 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	process_lexer_tokens(t_lexer *lexer, t_token **tokens)
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
	process_lexer_tokens(lexer, tokens);
	free(lexer);
	return (tokens);
}
