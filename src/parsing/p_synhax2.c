#include "../../includes/minishell.h"
#include "../../includes/parser.h"

static int	check_consecutive_redirections(t_token **tokens)
{
	int i = 0;
	
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

static int	check_pipe_syntax(t_token **tokens)
{
	int i = 0;
	
	if (tokens[0] && tokens[0]->type == PIPE)
	{
		print_syntax_error(tokens[0]->value);
		return (0);
	}
	while (tokens[i] && tokens[i]->type != END_OF_INPUT)
	{
		if (tokens[i]->type == PIPE)
		{
			if (!tokens[i + 1] || tokens[i + 1]->type == END_OF_INPUT || 
				tokens[i + 1]->type == PIPE)
			{
				print_syntax_error(tokens[i + 1] ? tokens[i + 1]->value : NULL);
				return (0);
			}
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
