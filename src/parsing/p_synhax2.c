/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_synhax2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:12:21 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:12:22 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

static int	check_consecutive_redirections(t_token **tokens)
{
	int	i;

	i = 0;
	while (tokens[i] && tokens[i]->type != END_OF_INPUT)
	{
		if (is_redirection_token(tokens[i]->type))
		{
			if (!check_redirection_target(tokens[i + 1]))
				return (0);
		}
		i++;
	}
	return (1);
}

static int	handle_pipe_error(t_token **tokens, int i)
{
	char	*error_value;

	error_value = NULL;
	if (tokens[i + 1])
		error_value = tokens[i + 1]->value;
	print_syntax_error(error_value);
	return (0);
}

static int	check_pipe_syntax(t_token **tokens)
{
	int		i;

	i = 0;
	if (tokens[0] && tokens[0]->type == PIPE)
	{
		print_syntax_error(tokens[0]->value);
		return (0);
	}
	while (tokens[i] && tokens[i]->type != END_OF_INPUT)
	{
		if (tokens[i]->type == PIPE)
		{
			if (!tokens[i + 1] || tokens[i + 1]->type == END_OF_INPUT
				|| tokens[i + 1]->type == PIPE)
				return (handle_pipe_error(tokens, i));
		}
		i++;
	}
	return (1);
}

int	check_syntax(t_token **tokens)
{
	if (!tokens || !tokens[0])
		return (1);
	if (!check_pipe_syntax(tokens))
		return (0);
	if (!check_consecutive_redirections(tokens))
		return (0);
	return (1);
}
