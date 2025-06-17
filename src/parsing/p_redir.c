/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_redir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:11:50 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:11:50 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_redir_type	token_to_redir_type(t_token_type token_type)
{
	if (token_type == REDIR_IN)
		return (REDIR_INPUT);
	else if (token_type == REDIR_OUT)
		return (REDIR_OUTPUT);
	else if (token_type == REDIR_APPEND)
		return (REDIR_APPEND_OUT);
	else if (token_type == HEREDOC)
		return (REDIR_HEREDOC_OUT);
	return (REDIR_INPUT);
}

t_redirect	*parse_redirection(t_token ***tokens_ptr, t_token_type redir_type)
{
	t_redirect	*redirect;

	if (!**tokens_ptr || (***tokens_ptr).type != WORD)
		return (NULL);
	redirect = (t_redirect *)malloc(sizeof(t_redirect));
	if (!redirect)
		return (NULL);
	redirect->type = token_to_redir_type(redir_type);
	redirect->file_or_delimiter = ft_strdup((***tokens_ptr).value);
	if (!redirect->file_or_delimiter)
	{
		free(redirect);
		return (NULL);
	}
	redirect->next = NULL;
	(*tokens_ptr)++;
	return (redirect);
}
