/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_syntax_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:13:08 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:14:13 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

void	print_syntax_error(char *token)
{
	ft_putstr_fd("MNM: syntax error near unexpected token `", 2);
	if (!token || !*token)
		ft_putstr_fd("newline", 2);
	else
		ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
}

int	is_redirection_token(t_token_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT
		|| type == REDIR_APPEND || type == HEREDOC);
}

int	check_redirection_target(t_token *token)
{
	if (!token || token->type == END_OF_INPUT)
	{
		print_syntax_error(NULL);
		return (0);
	}
	if (is_redirection_token(token->type))
	{
		print_syntax_error(token->value);
		return (0);
	}
	if (token->type != WORD && token->type != SQUOTE
		&& token->type != DQUOTE)
	{
		print_syntax_error(token->value);
		return (0);
	}
	return (1);
}
