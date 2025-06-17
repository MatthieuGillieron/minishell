#include "../../includes/minishell.h"
#include "../../includes/parser.h"

int	add_redirect(t_simple_cmd *cmd, t_redirect *redirect)
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
