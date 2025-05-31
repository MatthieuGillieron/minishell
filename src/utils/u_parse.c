#include "../../includes/minishell.h"

static void	free_redirects(t_redirect *redirect)
{
	t_redirect	*next;

	while (redirect)
	{
		next = redirect->next;
		free(redirect);
		redirect = next;
	}
}

static void	free_simple_cmd(t_simple_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->args)
	{
		free(cmd->args);
	}
	free_redirects(cmd->redirects);
	free(cmd);
}

void	free_command(t_command *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->commands)
	{
		i = 0;
		while (i < cmd->cmd_count)
		{
			free_simple_cmd(cmd->commands[i]);
			i++;
		}
		free(cmd->commands);
	}
	free(cmd);
}