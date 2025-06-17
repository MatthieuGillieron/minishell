/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_expand.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:11:42 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:11:42 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*process_dquote_token(t_token *token, t_env *env, t_status *status)
{
	char	*expanded;

	if (token->type != DQUOTE || !token->value)
		return (token);
	expanded = expand_variables(token->value, env, status);
	if (expanded)
	{
		free(token->value);
		token->value = expanded;
	}
	return (token);
}

t_token	*process_word_token(t_token *token, t_env *env, t_status *status)
{
	char	*expanded;

	if (token->type != WORD || !token->value)
		return (token);
	expanded = expand_variables(token->value, env, status);
	if (expanded)
	{
		free(token->value);
		token->value = expanded;
	}
	return (token);
}

void	expand_tokens(t_token **tokens, t_env *env, t_status *status)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->type == DQUOTE)
			process_dquote_token(tokens[i], env, status);
		else if (tokens[i]->type == WORD)
			process_word_token(tokens[i], env, status);
		i++;
	}
}
