/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_simple.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 11:12:12 by mg                #+#    #+#             */
/*   Updated: 2025/06/17 11:12:13 by mg               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

static int	add_arg(t_simple_cmd *cmd, char *arg)
{
	char	**new_args;
	int		i;

	new_args = (char **)malloc(sizeof(char *) * (cmd->arg_count + 2));
	if (!new_args)
		return (0);
	i = 0;
	while (i < cmd->arg_count)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[cmd->arg_count] = arg;
	new_args[cmd->arg_count + 1] = NULL;
	if (cmd->args)
		free(cmd->args);
	cmd->args = new_args;
	cmd->arg_count++;
	return (1);
}

static int	process_redir(t_simple_cmd *cmd, t_token ***tokens_ptr)
{
	t_token_type	redir_type;
	t_redirect		*redirect;

	redir_type = (***tokens_ptr).type;
	(*tokens_ptr)++;
	redirect = parse_redirection(tokens_ptr, redir_type);
	if (!redirect)
		return (0);
	return (add_redirect(cmd, redirect));
}

static int	handle_word_token(t_simple_cmd *cmd, t_token ***tokens_ptr)
{
	char	*value;

	if ((***tokens_ptr).value && (***tokens_ptr).value[0])
	{
		value = ft_strdup((***tokens_ptr).value);
		if (!value)
			return (0);
		if (!add_arg(cmd, value))
		{
			free(value);
			return (0);
		}
	}
	(*tokens_ptr)++;
	return (1);
}

static int	process_token(t_simple_cmd *cmd, t_token ***tokens_ptr)
{
	if ((***tokens_ptr).type == WORD
		|| (***tokens_ptr).type == SQUOTE
		|| (***tokens_ptr).type == DQUOTE)
		return (handle_word_token(cmd, tokens_ptr));
	else if ((***tokens_ptr).type == REDIR_IN
		|| (***tokens_ptr).type == REDIR_OUT
		|| (***tokens_ptr).type == REDIR_APPEND
		|| (***tokens_ptr).type == HEREDOC)
		return (process_redir(cmd, tokens_ptr));
	return (0);
}

t_simple_cmd	*parse_simple_command(t_token ***tokens_ptr)
{
	t_simple_cmd	*cmd;

	cmd = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->arg_count = 0;
	cmd->redirects = NULL;
	while (**tokens_ptr && (***tokens_ptr).type != PIPE
		&& (***tokens_ptr).type != END_OF_INPUT)
	{
		if (!process_token(cmd, tokens_ptr))
			return (NULL);
	}
	if (**tokens_ptr && (***tokens_ptr).type == END_OF_INPUT)
		(*tokens_ptr)++;
	return (cmd);
}
