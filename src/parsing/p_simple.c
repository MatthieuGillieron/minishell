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

static int	add_redirect(t_simple_cmd *cmd, t_redirect *redirect)
{
	t_redirect	*current;

	if (!cmd->redirects)
		cmd->redirects = redirect;
	else
	{
		current = cmd->redirects;
		while (current->next)
			current = current->next;
		current->next = redirect;
	}
	return (1);
}

static int	process_token(t_simple_cmd *cmd, t_token ***tokens_ptr)
{
	t_token_type	redir_type;
	t_redirect		*redirect;
	char			*value;

	if ((***tokens_ptr).type == WORD || 
		(***tokens_ptr).type == SQUOTE || 
		(***tokens_ptr).type == DQUOTE)
	{
		if ((***tokens_ptr).value && (***tokens_ptr).value[0])
        {
			value = ft_strdup((***tokens_ptr).value);
			if (!value || !add_arg(cmd, value))
				return (0);
        }
		(*tokens_ptr)++;
	}
	else if ((***tokens_ptr).type == REDIR_IN
		|| (***tokens_ptr).type == REDIR_OUT
		|| (***tokens_ptr).type == REDIR_APPEND
		|| (***tokens_ptr).type == HEREDOC)
	{
		redir_type = (***tokens_ptr).type;
		(*tokens_ptr)++;
		redirect = parse_redirection(tokens_ptr, redir_type);
		if (!redirect)
			return (0);
		if (!add_redirect(cmd, redirect))
			return (0);
	}
	else
		return (0);
	return (1);
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