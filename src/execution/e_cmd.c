#include "../../includes/minishell.h"

static void	execute_simple_cmd(t_simple_cmd *cmd, t_env **env, t_status *status)
{
	int	stdin_backup;
	int	stdout_backup;

	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (cmd->redirects)
	{
		if (apply_redirections(cmd->redirects) == -1)
		{
			status->exit_code = 1;
			dup2(stdin_backup, STDIN_FILENO);
			dup2(stdout_backup, STDOUT_FILENO);
			close(stdin_backup);
			close(stdout_backup);
			return ;
		}
	}
	execute_command(cmd->args, env, status);
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
}

void	execute_parsed_command(t_command *cmd, t_env **env, t_status *status)
{
	if (!cmd || !cmd->commands)
		return ;
	if (cmd->cmd_count == 1)
	{
		execute_simple_cmd(cmd->commands[0], env, status);
		return ;
	}
	execute_pipeline(cmd, env, status);
}
