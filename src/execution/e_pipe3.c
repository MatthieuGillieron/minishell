#include "../../includes/minishell.h"

/**
 * Crée les processus enfants et exécute les commandes du pipeline
 * @param cmd Structure de commande contenant le pipeline
 * @param env Pointeur vers l'environnement
 * @param status Structure contenant l'état du shell
 * @param data Structure contenant les données du pipeline
 */
void	execute_pipeline_commands(t_command *cmd, t_env **env, t_status *status,
								t_pipeline_data *data)
{
	int	i;

	handle_signals_parent();
	i = 0;
	while (i < cmd->cmd_count)
	{
		data->pids[i] = fork();
		if (data->pids[i] == -1)
		{
			perror("minishell: fork");
			status->exit_code = 1;
			break;
		}
		else if (data->pids[i] == 0)
		{
			setup_pipes(i, data->pipe_count, data->pipes);
			execute_child_process(cmd->commands[i], env, status);
		}
		i++;
	}
	close_all_pipes(data->pipes, data->pipe_count);
	wait_for_children(data->pids, cmd->cmd_count, status);
}
